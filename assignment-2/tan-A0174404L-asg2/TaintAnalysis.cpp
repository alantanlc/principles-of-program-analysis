/*
	Tan Lai Chian Alan
	A0174404L
	e0210437@u.nus.edu
*/

#include <cstdio>
#include <iostream>
#include <set>
#include <map>
#include <stack>

#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;
using namespace std;

std::string getSimpleNodeLabel(const BasicBlock *Node);
void printAnalysisMap(std::map<std::string, std::set<string>> analysisMap);

int main(int argc, char **argv)
{
	// Read the IR file.
	LLVMContext &Context = getGlobalContext();
	SMDiagnostic Err;

	// Extract Module M from IR (assuming only one Module exists)
	Module *M = ParseIRFile(argv[1], Err, Context);
	if (M == nullptr)
	{
		fprintf(stderr, "error: failed to load LLVM IR file \%s\"", argv[1]);
		return EXIT_FAILURE;
	}

	// 1.0 Extract Function main from Module M
	Function *F = M->getFunction("main");

	// 1.1 Create Analysis Map
	std::map<std::string, std::set<string>> analysisMap;
	for (auto &BB : *F) {
		std::set<string> instr;
		analysisMap[getSimpleNodeLabel(&BB)] = instr;
	}

	// 1.2 Create Set to store tainted addresses
	std::set<void*> tainted;

	// 2. Traversing the CFG in Depth First Order
	// In order to do so, we use a stack: traversalStack.
	// First, we add the entry basic block and an integer 0 representing depth to
	// the stack. The depth represents the distance of the BB from entryBB.
	std::stack<std::pair<BasicBlock*, int>> traversalStack;
	BasicBlock* entryBB = &F->getEntryBlock();
	std::pair<BasicBlock*, int> succAnalysisNode = std::make_pair(entryBB, 0);
	traversalStack.push(succAnalysisNode);

	// 3. while the stack is not empty we pop the top Basic Block, print it and
	// add its successor nodes to the stack plus an updated integer
	while(!traversalStack.empty()) {
		// Pop the top Basic Block and the depth from stack
		std::pair<BasicBlock*, int> succAnalysisNode = traversalStack.top();
		BasicBlock* BB = succAnalysisNode.first;
		int depth = succAnalysisNode.second;
		traversalStack.pop();

		std::cout << "Basic block: " << getSimpleNodeLabel(BB) << std::endl;

		// Add source to analysisMap
		analysisMap.at(getSimpleNodeLabel(BB)).insert("source");

		// Iterate through instructions to look for tainted variables
		for(auto &I: *BB) {
			I.dump();
			if(I.getOpcode() == 27) {	// load
				std::cout << "\tOpcodeName: " << I.getOpcodeName() << ", numOperands: " << I.getNumOperands() << std::endl;

				Value* v1 = I.getOperand(0);
				std::cout << "\tOperand 1 addr: " << (void*) v1 << std::endl;
				std::cout << "\tOperand 1 name: " << v1->getName().str() << std::endl;
				std::cout << "\tLoad addr: " << (void*) &I << std::endl;

				if(v1->getName().str() == "source") {
					// Add tainted addresses to set
					tainted.insert(v1);
					tainted.insert(&I);

					cout << "\t\tRegister " << (void*) &I << " has been tainted!\n";

					// Add variable to analysisMap
					analysisMap.at(getSimpleNodeLabel(BB)).insert(v1->getName());
				} else if (tainted.find(v1) != tainted.end()) {
					cout << "\t\tRegister " << (void*) &I << " has been tainted!\n";
					tainted.insert(&I);
					// analysisMap.at(getSimpleNodeLabel(BB)).insert(&I);
				}
			} else if (I.getOpcode() == 28) {	// store
				std::cout << "\tOpcodeName: " << I.getOpcodeName() << ", numOperands: " << I.getNumOperands() << std::endl;

				Value* v1 = I.getOperand(0);
				Value* v2 = I.getOperand(1);
				
				std::cout << "\tOperand 1 addr: " << (void*) v1 << ", operand 2 addr: " << (void*) v2 << std::endl;
				std::cout << "\tOperand 1 name: " << v1->getName().str() << ", operand 2 name: " << v2->getName().str() << std::endl;

				if(tainted.find(v1) != tainted.end()) {
					cout << "\t\t" << v2->getName().str() << " has been tainted!\n";
					tainted.insert(v2);

					analysisMap.at(getSimpleNodeLabel(BB)).insert(v2->getName());
				}
			}

			cout << "\n";
		}

		cout << "\n";

		// Extract the last instruction in the stack (Terminator Instruction)
		const TerminatorInst *TInst = BB->getTerminator();

		// Extract the number of successors the terminator instructor has
		int NSucc = TInst->getNumSuccessors();

		for (int i = 0; i < NSucc; ++i) {
			// For all successor basic blocks, add them to the stack
			// Increase the value of depth by 1
			BasicBlock *Succ = TInst->getSuccessor(i);
			std::pair<BasicBlock*, int> succAnalysisNode = std::make_pair(Succ, depth+1);
			traversalStack.push(succAnalysisNode);

			// Push top Basic Block's initialized variables to successor basic blocks
			auto var = analysisMap.at(getSimpleNodeLabel(BB));
			for (auto &I : var) {
				analysisMap.at(getSimpleNodeLabel(Succ)).insert(I);
			}
		}
	}

	// 4. Print result
	std::cout << std::endl;
	printAnalysisMap(analysisMap);

	return 0;
}

// Printing Basic Block Label
std::string getSimpleNodeLabel(const BasicBlock *Node) {
	if(!Node->getName().empty()) {
		return Node->getName().str();
	}
	std::string Str;
	raw_string_ostream OS(Str);
	Node->printAsOperand(OS, false);
	return OS.str();
}

// Print Analysis Map
void printAnalysisMap(std::map<std::string, std::set<string>> analysisMap) {
	std::cout << "Print Analysis Map\n";
	for(auto& row : analysisMap) {
		std::set<string> taintedVars = row.second;
		std::string BBLabel = row.first;
		errs() << BBLabel << ": { ";
		for(auto &var : taintedVars) {
			cout << var << ", ";
		}
		cout << "}\n";
	}
}

