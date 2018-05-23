#!/bin/bash

LLVM_DIR="$HOME/llvm-3.8"

### Cleaning up

rm -f *.so *.os


### Compiling LLVM pass

g++ -o StaticMetric.os -c -Wall -std=c++11 -Wformat=2 -Wextra -Werror -O3 -fomit-frame-pointer -fno-exceptions -fno-rtti -fPIC -Woverloaded-virtual -Wcast-qual -fPIC -DNDEBUG -D_GNU_SOURCE -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS -isystem $LLVM_DIR/include StaticMetric.cpp

g++ -o Passes.so -std=c++11 -Wall -Wformat=2 -Wextra -Werror -shared StaticMetric.os -L $LLVM_DIR/lib -lpthread -ldl -lm


### Compiling source code to apply pass to

clang -c -emit-llvm arclength.c -o arclength.bc


### Running pass

opt -load ./Passes.so -static-metric arclength.bc > /dev/null
