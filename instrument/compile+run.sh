#!/bin/bash

LLVM_DIR="$HOME/llvm-3.8"

### Cleaning up

rm -f *.so *.os *.bc


### Compiling LLVM pass

g++ -o Instrument.os -c -Wall -std=c++11 -Wformat=2 -Wextra -Werror -O3 -fomit-frame-pointer -fno-exceptions -fno-rtti -fPIC -Woverloaded-virtual -Wcast-qual -fPIC -DNDEBUG -D_GNU_SOURCE -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS -isystem $LLVM_DIR/include Instrument.cpp


### Compiling and linking source code to apply pass to

clang -c -emit-llvm arclength.c -o arclength.bc
clang -emit-llvm -c counters.c -o counters.bc
llvm-link -o temp.bc arclength.bc counters.bc


### Creating shared library

g++ -o Passes.so -Wall -std=c++11 -Wformat=2 -Wextra -Werror -shared Instrument.os -L $LLVM_DIR/lib -lpthread -ldl -lm 


### Instrumenting the code using the LLVM pass

opt -load ./Passes.so -instrument --exclude exclude_instrument.txt temp.bc > temp_i.bc

### Interpreting the instrumented bitcode
lli temp_i.bc
