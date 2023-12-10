#pragma once
#include "adj_list_solver.cc"

typedef size_t lit_id;

class WatchedLiteralsSolver : public AdjListSolver {
   public:
    WatchedLiteralsSolver(std::vector<clause>&& clauses, int num_vars) : AdjListSolver(std::move(clauses), num_vars), watched_literals(this->clauses.size(), {0, 1}) {}

    literal getImpliedLiteral(clause_id i, literal assignment) {
        const clause& c = clauses[i];
        auto& lits = watched_literals[i];
        if (-assignment == c[lits.first]) {
            if (!reassignWatchedLiteral(c, lits.first, lits.second)) {
                return c[lits.second];
            }
        } else if (-assignment == c[lits.second]) {
            if (!reassignWatchedLiteral(c, lits.second, lits.first)) {
                return c[lits.first];
            }
        }
        return 0;
    }

    bool reassignWatchedLiteral(const clause& c, lit_id& current_watched, lit_id other_watched) {
        for (lit_id i = 0; i < c.size(); i++) {
            if (getAssignment(c[i]) == UNASSIGNED && i != other_watched) {
                current_watched = i;
                return true;
            }
        }
        return false;
    }

   private:
    std::vector<std::pair<lit_id, lit_id>> watched_literals;
};