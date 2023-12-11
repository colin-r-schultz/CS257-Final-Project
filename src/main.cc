#include "watched_literals_solver.cc"
#include "ht_list_solver.cc"
#include "parse.cc"
#include <iostream>


int main(int argc, char *argv[]) {
    if (argc < 3) {
        std::cout << "Missing filename argument or solver type argument" << std::endl;
        return 1;
    }
    std::vector<clause> clauses;
    int num_vars = parse(argv[2], clauses);

    if (!strcmp(argv[1], "-a")) {
        AdjListSolver solver(std::move(clauses), num_vars);
        std::cout << solver.solve() << std::endl;
    } else if (!strcmp(argv[1], "-h")) {
        HTListSolver solver(std::move(clauses), num_vars);
        std::cout << solver.solve() << std::endl;
    } else if (!strcmp(argv[1], "-w")) {
        WatchedLiteralsSolver solver(std::move(clauses), num_vars);
        std::cout << solver.solve() << std::endl;
    } else {
        Solver solver(std::move(clauses), num_vars);
        std::cout << solver.solve() << std::endl;
    }

    return 0;
}