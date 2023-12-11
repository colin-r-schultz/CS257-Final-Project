#pragma once
#include <iostream>
#include <stack>
#include <vector>

typedef int literal;
typedef size_t clause_id;
typedef std::vector<literal> clause;

enum LiteralState { TRUE, FALSE, UNASSIGNED };

class Solver {
   public:
    Solver(std::vector<clause>&& clauses, int num_vars) : clauses(std::move(clauses)) {
        for (const clause& c : this->clauses) {
            if (c.size() == 1) {
                addAssignment(c[0]);
            }
        }
    }

    bool solve() {
        while (true) {
            while (!to_assign.empty()) {
                auto next_assignment = to_assign.back();
                to_assign.pop_back();
                const auto assignment = getAssignment(next_assignment);
                if (assignment == FALSE) {
                    // no decision points left
                    if (!backtrack()) {
                        printModel();
                        return false;
                    }
                } else if (assignment == UNASSIGNED) {
                    setMapping(next_assignment);
                    propagate(next_assignment);
                }
            }
            // nothing left to decide
            if (decide()) {
                printModel();
                return true;
            }
        }
    }

    void addAssignment(literal assignment) {
        to_assign.push_back(assignment);
    }

    void setMapping(literal assignment) {
        assignments.push_back(assignment);
    }

    virtual std::vector<clause_id> getRelevantClauses(literal assignment) {
        std::vector<clause_id> result;
        for (size_t i = 0; i < clauses.size(); i++) {
            for (const literal l : clauses[i]) {
                if (l == -assignment) {
                    result.push_back(i);
                }
            }
        }
        return result;
    }

    void propagate(literal assignment) {
        // printModel();
        for (const clause_id i : getRelevantClauses(assignment)) {
            literal implied = getImpliedLiteral(i, assignment);
            if (implied != 0) {
                // std::cout << "clause " << i << " implied " << implied << std::endl;
                addAssignment(implied);
            }
        }
    }

    virtual literal getImpliedLiteral(clause_id i, literal assignment) {
        literal implied = 0;
        for (const literal lit : clauses[i]) {
            LiteralState state = getAssignment(lit);
            if (state == TRUE) {
                return 0;
            }
            if (state == UNASSIGNED) {
                if (implied == 0) {
                    implied = lit;
                } else {
                    return 0;
                }
            }
        }
        return implied;
    }

    LiteralState getAssignment(literal var) {
        for (const literal assignment : assignments) {
            if (assignment == var) {
                return TRUE;
            }
            if (assignment == -var) {
                return FALSE;
            }
        }
        return UNASSIGNED;
    }

    virtual bool decide() {
        for (const clause& c : clauses) {
            for (const literal lit : c) {
                if (getAssignment(lit) == UNASSIGNED) {
                    decision_points.push_back(assignments.size());
                    // std::cout << "deciding " << lit << std::endl;
                    addAssignment(lit);
                    return false;
                }
            }
        }
        return true;
    }

    virtual bool backtrack() {
        if (decision_points.empty()) {
            return false;
        }
        auto decision_point = assignments.begin() + decision_points.back();
        literal bad_decision = *decision_point;
        assignments.erase(decision_point, assignments.end());
        to_assign.clear();
        decision_points.pop_back();
        addAssignment(-bad_decision);
        return true;
    }

    void printModel() {
        for (const literal lit : assignments) {
            std::cout << lit << " ";
        }
        std::cout << std::endl;
    }

   protected:
    std::vector<literal> to_assign;

    std::vector<literal> assignments;
    std::vector<size_t> decision_points;
    std::vector<clause> clauses;
};