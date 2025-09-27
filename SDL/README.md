# Simple graphical example
This is example of graphical application with simple interface based on the SDL 2.0.

## Conway's Game of Life
**Conway's Game of Life** is a zero-player cellular automaton created by mathematician John Conway.  
It unfolds on a grid where cells live or die based on simple rules of neighbor counts.  
This deterministic system requires no further input after the initial configuration.  

### Rules
* Any live cell with fewer than two live neighbors dies, as if by underpopulation.
* Any live cell with two or three live neighbors lives on to the next generation.
* Any live cell with more than three live neighbors dies, as if by overpopulation.
* Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.    
* The grid is cyclical, meaning the top and bottom edges are connected, and the left and right edges are connected. This effectively turns the finite grid into the surface of a torus (a doughnut shape).

## Preview
![alt text](images/conway.gif)

## Usage:
Simple run:
```
sudo apt install libsdl2-dev
clang start.c sim.c app.c -lSDL2
./a.out
```
## Generate LLVM IR
```
# Generate .ll files
clang start.c sim.c app.c -emit-llvm -S -O1
```

```
# Bound modules
llvm-link start.ll sim.ll app.ll -o combined.bc
```

```
# Interpret with loading SDL2
lli --load=$(find /usr -name "libSDL2.so" 2>/dev/null | head -n1) combined.bc
```

There are some ```LLVM IR``` and ```combined.bc``` with different flags for ```app.c``` module in ```IR/``` directory.

## Instructions task
In file ```instructions/main.c``` are some little examples of programs to see instructions from the list:
* trunc
* getelementptr
* srem
* lshr
* zext
* bitcast
* sitofp
* select
* fpext
* tail call
```
# Other commands are before examples in file instructions/main.c
clang main.c -emit-llvm -S -O0 -D TRUNC
```

## SDL 2.0 documentation:
https://wiki.libsdl.org