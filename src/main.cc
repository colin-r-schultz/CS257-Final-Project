#include "adj_list_solver.cc"
#include <iostream>

int main() {
    std::vector<clause> clauses = {{1}, {-1, -2}, {2, -1}};
    AdjListSolver solver(clauses, 2);
    std::cout << solver.solve() << std::endl;
    return 0;
}