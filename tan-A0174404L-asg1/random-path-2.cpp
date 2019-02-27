#include <cstdio>
#include <iostream>
#include <set>
#include <cstdlib>
#include <ctime>

#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

void generatePath(BasicBlock* BB);
std::string getSimpleNodeLabel(const BasicBlock *Node);
std::set<llvm::BasicBlock*> stack;

int main(int argc, char **argv) {
	// Read the IR file
	LLVMContext &Context = getGlobalContext();
	SMDiagnostic Err;
	Module *M = ParseIRFile(argv[1], Err, Context);
	if (M == nullptr)
	{
		fprintf(stderr, "error: failed to load LLVM IR file \%s\"", argv[1]);
		return EXIT_FAILURE;
	}

	for (auto &F: *M) {
		if (strncmp(F.getName().str().c_str(), "main", 4) == 0) {
			BasicBlock* BB = dyn_cast<BasicBlock>(F.begin());
			llvm:outs() << "Label:" << getSimpleNodeLabel(BB) << "\n";
			generatePath(BB);
			stack.insert(BB);
		}
	}
	return 0;
}

void generatePath(BasicBlock* BB) {
	const TerminatorInst *TInst = BB->getTerminator();
	unsigned NSucc = TInst->getNumSuccessors();
	if(NSucc == 1) {
		BasicBlock *Succ = TInst->getSuccessor(0);
		if(stack.find(Succ) == stack.end()) {
			stack.insert(Succ);
			llvm::outs() << "Label:" << getSimpleNodeLabel(Succ) << "\n";
			generatePath(Succ);
		}
	}
}
