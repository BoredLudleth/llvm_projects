# LLVM IR-generator
In this task we are generating IR, then compiling it with graph lib and launch (via ExecutionEngine)

## Usage:
For building and using IR-generator you should run this commands in shell:
```
clang++ -O2 ir_gen.cpp sim.c $(llvm-config --cppflags --ldflags --libs) -lSDL2
./a.out
```
