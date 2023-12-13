# CS257 Final Project
This repository contains the code for a SAT solver created for our final project for CS257.

### Building
To build the project, just compile `src/main.cc` with any C++ compiler.

For example:
```
g++ -std=c++17 -O3 src/main.cc -o solver
```

### Running
Run the solver by selecting an optimization and CNF file.

For example:
```
./solver -w benchmarks/benchmark1.cnf
```
The program will first print the model it finds as a list of literals. Then it will print 0 if the problem is unsatisfiable or 1 if the program is satisfiable.

Solver options:
* `-b` - run the baseline solver
* `-a` - run the solver with adjancency lists
* `-h` - run the solver with adjancency lists and H/T lists
* `-w` - run the solver with adjancency lists and watched literals

The benchmarks used in the writeup are available in the `benchmarks/` directory.
