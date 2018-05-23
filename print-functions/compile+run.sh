#!/bin/bash

LLVM_DIR="$HOME/llvm-3.8"

### Cleaning up

rm -f *.so *.os


### Compiling LLVM pass

g++ -o PrintFunctionNames.os -c -Wall -std=c++11 -Wformat=2 -Wextra -Werror -O3 -fomit-frame-pointer -fno-exceptions -fno-rtti -fPIC -Woverloaded-virtual -Wcast-qual -fPIC -DNDEBUG -D_GNU_SOURCE -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS -isystem $LLVM_DIR/include PrintFunctionNames.cpp

g++ -o Passes.so -Wall -std=c++11 -Wformat=2 -Wextra -Werror -shared PrintFunctionNames.os -L $LLVM_DIR/lib -lpthread -ldl -lm


### Compiling source code to apply pass to

clang -c -g -emit-llvm arclength.c -o arclength.bc


### Running pass

opt -load ./Passes.so -print-names arclength.bc > /dev/null
