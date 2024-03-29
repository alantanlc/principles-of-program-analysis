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

int main(int argc, char **argv)
{
    // Read the IR file.
    LLVMContext &Context = getGlobalContext();
    SMDiagnostic Err;

    // Extract Module M from IR (assuming only one Module exists)
    Module *M = ParseIRFile(argv[1], Err, Context);
    if (M == nullptr)
    {
      fprintf(stderr, "error: failed to load LLVM IR file \"%s\"", argv[1]);
      return EXIT_FAILURE;
    }

    // 1.Extract Function main from Module M
    Function *F = M->getFunction("main");
    
    // 2. Traversing the CFG in Depth First Order
    // In order to do so, we use a stack: traversalStack.
    // First, we add the entry basic block and a integer 0 representing depth to 
    // the stack. The depth represents the distance of the BB from entryBB.  
    std::stack<std::pair<BasicBlock*,int>> traversalStack;
    BasicBlock* entryBB = &F->getEntryBlock();
    std::pair<BasicBlock*,int > succAnalysisNode = std::make_pair(entryBB,0);
    traversalStack.push(succAnalysisNode);
    
    // 3. while the stack is not empty we pop the top Basic Block, print it and
    // add it's successor nodes to the stack plus an updated integer
    while(!traversalStack.empty()){
        // Pop the top Basic Block and the depth from stack
        std::pair<BasicBlock*,int > succAnalysisNode = traversalStack.top();
        BasicBlock* BB = succAnalysisNode.first;
        int depth = succAnalysisNode.second;
      	traversalStack.pop();
      	
	// Print the Basic Block, depth is used for pretty printing
      	if(BB != entryBB){
            for (int i = 0; i < 2*depth; i++)
	        llvm::outs() << " ";
            llvm::outs() << "| \n";
        }
        for (int i = 0; i < 2*depth; i++)
	    llvm::outs() << " ";        
        llvm::outs() << "Label:" << getSimpleNodeLabel(BB) << "\n";

        // Extract the last instruction in the stack (Terminator Instruction)
        const TerminatorInst *TInst = BB->getTerminator();
        
        // Extract the number of successors the terminator instructor has
	int NSucc = TInst->getNumSuccessors();

	for (int i = 0;  i < NSucc; ++i) {
            // For all successor basic blocks, add them to the stack
	    // Increase the value of depth by 1
            BasicBlock *Succ = TInst->getSuccessor(i);    
            std::pair<BasicBlock*,int > succAnalysisNode = std::make_pair(Succ,depth+1);
            traversalStack.push(succAnalysisNode);
    	}	
    }
    
    return 0;
}

// Printing Basic Block Label 
std::string getSimpleNodeLabel(const BasicBlock *Node) {
    if (!Node->getName().empty())
        return Node->getName().str();
    std::string Str;
    raw_string_ostream OS(Str);
    Node->printAsOperand(OS, false);
    return OS.str();
}
