## CS5218 Assignment 3 - Abstract Interpretation
## Tan Lai Chian Alan
## A0174404L
## e0210437@u.nus.edu

## Generate .ll files
clang++-3.5 -emit-llvm -S -o ./test-files/test2.ll ./test-files/test2.c

## Build for Part 1 Task 2
clang++-3.5 -o absInt1 absInt1.cpp `llvm-config-3.5 --cxxflags` `llvm-config-3.5 --ldflags` `llvm-config-3.5 --libs` -lpthread -lncurses -ldl

## Build for Part 1 Task 3
clang++-3.5 -o absInt2 absInt2.cpp `llvm-config-3.5 --cxxflags` `llvm-config-3.5 --ldflags` `llvm-config-3.5 --libs` -lpthread -lncurses -ldl

## Test for Part 1 Task 2
./absInt1 ./test-files/test2.ll

## Test for Part 1 Task 3
./absInt2 ./test-files/test3.ll
