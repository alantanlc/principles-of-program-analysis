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

std::string getSimpleNodeLabel(const BasicBlock *Node);
void printAnalysisMap(std::map<std::string, std::set<Instruction*>> analysisMap);

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

	// 1. Extract Function main from Module M
	Function *F = M->getFunction("main");

	// 1.5 Create Analysis Map
	std::map<std::string, std::set<Instruction*>> analysisMap;
	for (auto &BB : *F) {
		std::set<Instruction*> emptySet;
		analysisMap[getSimpleNodeLabel(&BB)] = emptySet;
	}

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

		// Iterate through instructions to look for initialized variables
		for(auto &I: *BB) {
			if(isa<StoreInst>(I)) {
				Value* v = I.getOperand(1);	// retrieving second argument
				Instruction* var = dyn_cast<Instruction>(v);
				//var->dump();

				// Push initialized variable to analysis map
				if(var) {
					analysisMap.at(getSimpleNodeLabel(BB)).insert(var);
				}
			}
		}

		// Extract the last instruction in the stack (Terminator Instruction)
		const TerminatorInst *TInst = BB->getTerminator();

		// Extract the number of successors the terminator instructor has
		int NSucc = TInst->getNumSuccessors();

		// For each successor
		for (int i = 0; i < NSucc; ++i) {
			BasicBlock *Succ = TInst->getSuccessor(i);

			// Check if top Basic Block's initialized variables exist in successor Basic Block
			// If no, means Analysis has changed for successor. In this case, set "hasChanged" to true and push initialized variable to analysisMap of successor
			bool hasChanged = false;
			auto var = analysisMap.at(getSimpleNodeLabel(BB));
			for (auto &I : var) {
				if(analysisMap.at(getSimpleNodeLabel(Succ)).find(I) == analysisMap.at(getSimpleNodeLabel(Succ)).end()) {
					hasChanged = true;
					analysisMap.at(getSimpleNodeLabel(Succ)).insert(I);
				}
			}

			// If Analysis has changed, push successor Basic Block to traversal stack
			if (hasChanged) {
				std::pair<BasicBlock*, int> succAnalysisNode = std::make_pair(Succ, depth+1);
				traversalStack.push(succAnalysisNode);
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
void printAnalysisMap(std::map<std::string, std::set<Instruction*>> analysisMap) {
	std::cout << "Print Analysis Map\n";
	for(auto& row : analysisMap) {
		std::set<Instruction*> initializedVars = row.second;
		std::string BBLabel = row.first;
		errs() << BBLabel << ":\n";
		for(Instruction* var : initializedVars) {
			errs() << "\t";
			var->dump();
		}
		errs() << "\n";
	}
}

