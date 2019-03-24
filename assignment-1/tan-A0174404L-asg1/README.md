## Tan Lai Chian Alan
## A0174404L
## e0210437@u.nus.edu

## Generate .ll files
clang-3.5 -emit-llvm -S -o test1.ll test1.c
clang-3.5 -emit-llvm -S -o test2.ll test2.c
clang-3.5 -emit-llvm -S -o test3.ll test3.c
clang-3.5 -emit-llvm -S -o test4.ll test4.c
clang-3.5 -emit-llvm -S -o test5.ll test5.c
clang-3.5 -emit-llvm -S -o test6.ll test6.c

## Build
clang++-3.5 -o initialized-variables initialized-variables.cpp `llvm-config-3.5 --cxxflags` `llvm-config-3.5 --ldflags` `llvm-config-3.5 --libs` -lpthread -lncurses -ldl

clang++-3.5 -o initialized-variables-bonus initialized-variables-bonus.cpp `llvm-config-3.5 --cxxflags` `llvm-config-3.5 --ldflags` `llvm-config-3.5 --libs` -lpthread -lncurses -ldl

## Task 2
./initialized-variables ./test-files/test1.ll
./initialized-variables ./test-files/test2.ll
./initialized-variables ./test-files/test3.ll
./initialized-variables ./test-files/test4.ll
./initialized-variables ./test-files/test5.ll
./initialized-variables ./test-files/test6.ll

## Task 3
./initialized-variables-bonus ./test-files/test1.ll
./initialized-variables-bonus ./test-files/test2.ll
./initialized-variables-bonus ./test-files/test3.ll
./initialized-variables-bonus ./test-files/test4.ll
./initialized-variables-bonus ./test-files/test5.ll
./initialized-variables-bonus ./test-files/test6.ll
