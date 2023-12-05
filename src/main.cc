#include "adj_list_solver.cc"
#include "parse.cc"
#include <iostream>

int main() {
    Parser parser("../small_files/pigeon5.txt");
    size_t num_vars = parser.get_num_vars();
    std::vector<clause> clauses = parser.get_clauses();

    AdjListSolver solver(clauses, num_vars);
    std::cout << solver.solve() << std::endl;
    return 0;
}