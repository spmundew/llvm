#include "PrintFunctionNames.hpp"

#include <llvm/IR/Instructions.h>
#include <llvm/IR/Module.h>
#include <llvm/Support/raw_ostream.h>

using namespace std;
using namespace llvm;


bool PrintFunctionNames::runOnModule(Module &M) {
  
  errs() << "Pass PrintFunctionNames\n";
  
  // iterating through functions
  for(Module::iterator f = M.begin(), fe = M.end(); f != fe; f++) {
    errs() << "Function name: " << f->getName() << "\n";
  }

  return false;
}  


void PrintFunctionNames::getAnalysisUsage(AnalysisUsage &AU) const {
  AU.setPreservesAll();
}


char PrintFunctionNames::ID = 0;
static const RegisterPass<PrintFunctionNames> registration("print-names", "Printing function names");
