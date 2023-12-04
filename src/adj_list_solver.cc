#pragma once
#include "solver.cc"

class AdjListSolver : public Solver {
   public:
    AdjListSolver(std::vector<clause> clauses, int num_vars) : Solver(clauses, num_vars), positive_adjacency_lists(num_vars + 1), negative_adjacency_lists(num_vars + 1) {
        for (clause_id i = 0; i < clauses.size(); i++) {
            for (const literal lit : clauses[i]) {
                if (lit < 0) {
                    positive_adjacency_lists[-lit].push_back(i);
                } else {
                    negative_adjacency_lists[lit].push_back(i);
                }
            }
        }
    }

    virtual std::vector<clause_id> getRelevantClauses(literal assignment) {
        if (assignment < 0) {
            return negative_adjacency_lists[-assignment];
        } else {
            return positive_adjacency_lists[assignment];
        }
    }

   private:
    std::vector<std::vector<clause_id>> positive_adjacency_lists;
    std::vector<std::vector<clause_id>> negative_adjacency_lists;
};