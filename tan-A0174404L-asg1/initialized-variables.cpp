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

		// Compute initialized variables
		llvm::outs() << "Label: " << getSimpleNodeLabel(BB) << "\n";
		for(auto &I: *BB) {	// Iterate through instructions to look for initialized variables
			if(isa<StoreInst>(I)) {
				Value* v = I.getOperand(1);	// retrieving second argument
				Instruction* var = dyn_cast<Instruction>(v);
				var->dump();

				// Push initialized variable to analysis map
				analysisMap.at(getSimpleNodeLabel(BB)).insert(var);
			}
		}

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

