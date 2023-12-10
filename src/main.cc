#include "adj_list_solver.cc"
#include "parse.cc"
#include <iostream>

int main() {
    std::vector<clause> clauses;
    int num_vars = parse("../small_files/pigeon5.txt", clauses);
    print_clauses(clauses);
    AdjListSolver solver(std::move(clauses), num_vars);
    // std::cout << solver.solve() << std::endl;
    return 0;
}