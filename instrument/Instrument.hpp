#ifndef INSTRUMENT_GUARD
#define INSTRUMENT_GUARD 1

#include <llvm/IR/DebugInfo.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Module.h>
#include <llvm/Pass.h>
#include <llvm/Support/CommandLine.h>

#include <set>

namespace llvm {
	class Value;
	class BinaryOperator;
	class FCmpInst;
	class Type;
}

using namespace std;
using namespace llvm;
cl::opt<string> ExcludedFunctionsFileName("exclude", cl::value_desc("filename"), cl::desc("List of functions to exclude (if in dependencies)"), cl::init("exclude.txt"));


class Instrument : public ModulePass {
public:
  Instrument() : ModulePass(ID) {}

  virtual bool doInitialization(Module &module);

  bool runOnFunction(Module &module, Function &function);

  virtual void getAnalysisUsage(AnalysisUsage &AU) const;

  virtual bool runOnModule(Module &module);

  static char ID; // Pass identification, replacement for typeid

private:
  set<string> excludedFunctions;

  DebugInfoFinder debugInfo;  
};

#endif
