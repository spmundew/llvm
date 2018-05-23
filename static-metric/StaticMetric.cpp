#include "StaticMetric.hpp"

#include <llvm/IR/Instructions.h>
#include "llvm/Transforms/Utils/BasicBlockUtils.h"
#include <llvm/Support/raw_ostream.h>

bool StaticMetric::doInitialization(Module &M) {
  debugInfo.processModule(M);
  castInstCount = 0;
  score = 0;
  arithOp["float"] = 0;
  arithOp["double"] = 0;
  arithOp["longdouble"] = 0;
  cmpOp["float"] = 0;
  cmpOp["double"] = 0;
  cmpOp["longdouble"] = 0;
  loadOp["float"] = 0;
  loadOp["double"] = 0;
  loadOp["longdouble"] = 0;
  storeOp["float"] = 0;
  storeOp["double"] = 0;
  storeOp["longdouble"] = 0;
  return false;
}

bool StaticMetric::runOnModule(Module &M) {
  for(Module::iterator f = M.begin(), fe = M.end(); f != fe; f++) {
    if (!f->isDeclaration()) {
      runOnFunction(*f);
    }
  }
  return false;
}

bool StaticMetric::runOnFunction(Function &F) {
  for (Function::iterator b = F.begin(), be = F.end(); b != be; b++) {
    for (BasicBlock::iterator i = b->begin(), ie = b->end(); i != ie; i++) {
      Instruction *inst = (Instruction*)i;
      Value *val = NULL;
      if (dyn_cast<CastInst>(inst)) {
	castInstCount++;
      } else if (FCmpInst* target = dyn_cast<FCmpInst>(inst)) {
	val = target->getOperand(0);
	increaseCounter(val->getType(), cmpOp);
      } else if (BinaryOperator *target = dyn_cast<BinaryOperator>(inst)) {
	val = target->getOperand(0);
	increaseCounter(val->getType(), arithOp);
      } else if (LoadInst *target = dyn_cast<LoadInst>(inst)) {
	val = target->getPointerOperand();
	PointerType* pointerType = (PointerType*) val->getType();
	increaseCounter(pointerType->getElementType(), loadOp);
      } else if (StoreInst* target = dyn_cast<StoreInst>(inst)) {
	val = target->getOperand(0);
	increaseCounter(val->getType(), storeOp);
      }
    }
  }
  return false;
}

void StaticMetric::increaseCounter(Type* type, map<string, int> &counter) {
  if (type->isFloatTy()) {
    counter["float"]++;
    score = score + 32;
  } else if (type->isDoubleTy()) {
    counter["double"]++;
    score = score + 64;
  } else if (type->isX86_FP80Ty()) {
    counter["longdouble"]++;
    score = score + 80;
  } 
  return;
}

void StaticMetric::printCounter(map<string, int> &counter) {
  errs() << "\tfloat: " << counter["float"] << "\n";
  errs() << "\tdouble: " << counter["double"] << "\n";
  errs() << "\tX86_FP80: " << counter["longdouble"] << "\n";
  return;
}

bool StaticMetric::doFinalization(Module &M __attribute__((unused))) {
  errs() << "The number of casting instruction: " << castInstCount << "\n";
  errs() << "The number of arithmetic operations:\n";
  printCounter(arithOp);
  errs() << "The number of comparison operations:\n";
  printCounter(cmpOp);
  errs() << "The number of load instructions:\n";
  printCounter(loadOp);
  errs() << "The number of store instructions:\n";
  printCounter(storeOp);
  errs() << "The score is:" << score << "\n";
  return false;
}

void StaticMetric::getAnalysisUsage(AnalysisUsage &AU) const {
  AU.setPreservesAll();
}

char StaticMetric::ID = 0;

static const RegisterPass<StaticMetric> registration("static-metric", "Print static metric information");
