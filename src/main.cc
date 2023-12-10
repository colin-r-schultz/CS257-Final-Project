#include "adj_list_solver.cc"
#include "parse.cc"
#include <iostream>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "Missing filename argument" << std::endl;
        return 1;
    }
    std::vector<clause> clauses;
    int num_vars = parse(argv[1], clauses);
    print_clauses(clauses);
    AdjListSolver solver(std::move(clauses), num_vars);
    std::cout << solver.solve() << std::endl;
    return 0;
}