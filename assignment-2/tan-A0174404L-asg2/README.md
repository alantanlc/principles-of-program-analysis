## Tan Lai Chian Alan
## A0174404L
## e0210437@u.nus.edu

## Generate .ll files
clang-3.5 -emit-llvm -S -o ./test-files/test1.ll ./test-files/test1.c
clang-3.5 -emit-llvm -S -o ./test-files/test2.ll ./test-files/test2.c
clang-3.5 -emit-llvm -S -o ./test-files/test3.ll ./test-files/test3.c

## Build
clang++-3.5 -o TaintAnalysis TaintAnalysis.cpp `llvm-config-3.5 --cxxflags` `llvm-config-3.5 --ldflags` `llvm-config-3.5 --libs` -lpthread -lncurses -ldl

clang++-3.5 -o TaintAnalysisLoop TaintAnalysisLoop.cpp `llvm-config-3.5 --cxxflags` `llvm-config-3.5 --ldflags` `llvm-config-3.5 --libs` -lpthread -lncurses -ldl

## Example 1
./TaintAnalysis ./test-files/test1.ll

## Example 2
./TaintAnalysis ./test-files/test2.ll

## Example 3
./TaintAnalysisLoop ./test-files/test3.ll
