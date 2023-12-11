#pragma once
#include "adj_list_solver.cc"

typedef size_t lit_id;

class HTListSolver : public AdjListSolver {
    public:
        HTListSolver(std::vector<clause>&& clauses, int num_vars) : AdjListSolver(std::move(clauses), num_vars) {
            for (const clause& c : this->clauses) {
                if (c.size() == 1) {
                    cur_ht_assignment.push_back({0, 0});
                    ht_at_decision_pt.push_back({{0, 0}});
                } else {
                    cur_ht_assignment.push_back({0, c.size() - 1});
                    ht_at_decision_pt.push_back({{0, c.size() - 1}});
                }
            }
        }

        virtual literal getImpliedLiteral(clause_id i, literal assignment) {
            lit_id head = cur_ht_assignment[i].first;
            lit_id tail = cur_ht_assignment[i].second;

            if (clauses[i][head] == -assignment) {
                while ((getAssignment(clauses[i][head]) == FALSE) && (head != tail)) {
                    head += 1;
                }  
            } else if (clauses[i][tail] == -assignment) {
                while ((getAssignment(clauses[i][tail]) == FALSE) && (head != tail)) {
                    tail -= 1;
                }
            }

            cur_ht_assignment[i] = {head, tail};

            if (head == tail) {
                return clauses[i][head];
            } else {
                return 0;
            }
        }

        void print_vec(std::vector<std::pair<lit_id, lit_id>> vec) {
            for (std::pair<lit_id, lit_id> p : vec) {
                std::cout << "{" << p.first << ", " << p.second << "} ";
            }
            std::cout << std::endl;
        }

        void print_nested_vec(std::vector<std::vector<std::pair<lit_id, lit_id>>> vec) {
            for (std::vector<std::pair<lit_id, lit_id>> v : vec) {
                std::cout << "{";
                for (std::pair<lit_id, lit_id> p : v) {
                    std::cout << "{" << p.first << ", " << p.second << "}";
                }
                std::cout << "} ";
            }
            std::cout << std::endl;
        }

        void update_ht_decision_pt() {
            for (size_t i = 0; i < clauses.size(); i++) {
                ht_at_decision_pt[i].push_back(cur_ht_assignment[i]);
            }
        }

        virtual bool decide() {
            for (const clause& c : clauses) {
                for (const literal lit : c) {
                    if (getAssignment(lit) == UNASSIGNED) {
                        decision_points.push_back(assignments.size());
                        std::cout << "deciding " << lit << std::endl;
                        addAssignment(lit);
                        update_ht_decision_pt();
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

            for (size_t i = 0; i < clauses.size(); i++) {
                cur_ht_assignment[i] = ht_at_decision_pt[i].back();
                ht_at_decision_pt[i].pop_back();
            }

            return true;
        }

    private:
        std::vector<std::pair<lit_id, lit_id>> cur_ht_assignment;
        std::vector<std::vector<std::pair<lit_id, lit_id>>> ht_at_decision_pt;
};
