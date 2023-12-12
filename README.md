CS257

Build the project:

`cd src`
`g++ -std=c++17 main.cc -o build/solver`

Run different versions of the solver, for example `./build/solver -w ../benchmarks/benchmark1.cnf` runs the watched literal solver on the first benchmark. 

Use `-h`, `-a`, or `-b` to run the H/T list, adjacency list, or baseline implementations respectively. 