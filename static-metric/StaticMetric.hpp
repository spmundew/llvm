#ifndef STATIC_METRIC_GUARD
#define STATIC_METRIC_GUARD 1

#include <llvm/IR/DebugInfo.h>
#include <llvm/Pass.h>
#include <llvm/IR/Module.h>

#include <map>
#include <string>

namespace llvm {
  class Type;
}

using namespace std;
using namespace llvm;

class StaticMetric : public ModulePass {
  
public:
  StaticMetric() : ModulePass(ID) {}
  
  virtual bool doInitialization(Module &M);
  
  virtual void getAnalysisUsage(AnalysisUsage &AU) const;

  virtual bool runOnModule(Module &M);

  bool runOnFunction(Function &F);

  void increaseCounter(Type* type, map<string, int> &counter);

  void printCounter(map<string, int> &counter);
  
  virtual bool doFinalization(Module &M);

  static char ID; // Pass identification, replacement for typeid

private:
  DebugInfoFinder debugInfo;

  int score; // total score

  int castInstCount; // Counter of cast isntructions

  map<string, int> arithOp; // Counter of airthmetic operations 

  map<string, int> cmpOp; // Counter of comparision operations

  map<string, int> loadOp; // Counter of load instructions

  map<string, int> storeOp; // Counter of store instructions

};

#endif
