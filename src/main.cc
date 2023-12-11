#include "watched_literals_solver.cc"
#include "ht_list_solver.cc"
#include "parse.cc"
#include <iostream>

#define HT_LIST

#ifdef WATCHED_LITS
    typedef WatchedLiteralsSolver SolverTy;
#elifdef HT_LIST
    typedef HTListSolver SolverTy;
#else
    typedef Solver SolverTy;
#endif

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "Missing filename argument" << std::endl;
        return 1;
    }
    std::vector<clause> clauses;
    int num_vars = parse(argv[1], clauses);
    HTListSolver solver(std::move(clauses), num_vars);
    std::cout << solver.solve() << std::endl;
    return 0;
}