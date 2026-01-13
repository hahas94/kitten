# kitten
Solutions to programming problems on the [Kattis](https://open.kattis.com//) Problem Archive.
C++ is the main language for writing the code hence this repo is CMake-based.

## Setup
Create the build directories for both release and debug:  
```
mkdir -p build build/release build/debug
```

Prepare a Release/Debug C++23 build using GCC 14:
```
cmake -B build/release -S . -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=gcc-14 -DCMAKE_CXX_COMPILER=g++-14 -DCMAKE_CXX_STANDARD=23
```
```
cmake -B build/debug -S . -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_COMPILER=gcc-14 -DCMAKE_CXX_COMPILER=g++-14 -DCMAKE_CXX_STANDARD=23
```

Building the project:
```
cmake --build build/debug
```

Finally, running the main file for the `puzzles/pieces` problem and comparing 
the result with the actual output:
```
./build/debug/puzzles/pieces/pieces < puzzles/pieces/sample.in | diff -c - puzzles/pieces/sample.output
```

## Scripts
There are three scripts for automating file/directory creation with 
boilerplate code. When run at the root:

`./template.sh puzzles pieces` creates a subdirectory for the problem 
`pieces` with a main file as well as input/output files inside the `puzzles` 
directory. If `puzzles` directory does not exist, then it is created as well.  

`./algo_template.sh inverse` creates a header and an implementation file for 
the `inverse` algorithm in the `algorithms` directory. 

`./kattis_template.sh math/fastinverse inverse` creates a single file that can 
be used for submission by merging the code from the `fastinverse` problem and 
the `inverse` algorithm, as it is assumed that the solution to this problem uses 
the specified algorithm.

## Algorithms
A library implementing some advanced algorithms for usage in problem-solving. 
It includes algorithms from several different areas, listed below. 

## Problem areas:
- Data structures   
```
┌───┬───┬───┬───┐
│ x │ y │ z │ w │
└───┴───┴───┴───┘
```
- Recursion/Dynamic programming
```
┌─────┐
│  f  │
│ ┌───┐│
│ │ f ││
│ │┌──┐│
│ ││ f││
│ │└──┘│
│ └───┘│
└─────┘
```
- Geometry
```
A ●──────● B
       /
      /
     ● C
```
- Greedy algorithms
```
S ── 8 ── 3 ── 1
\
6 ── 4 ── 2
```
- Miscellaneous/Simulation problems
```
●   ▲   ■   ★   ◆  ○ ─ □ ─ △ ─ ☆ ─ ◇
```

### Author
Hardy Hasan
