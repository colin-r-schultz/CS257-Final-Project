#pragma once
#include "adj_list_solver.cc"

typedef size_t lit_id;

class HTListSolver : public AdjListSolver {
    public:
        HTListSolver(std::vector<clause>&& clauses, int num_vars) : AdjListSolver(std::move(clauses), num_vars) {
            for (const clause& c : this->clauses) {
                if (c.size() == 1) {
                    ht_at_decision_pt.push_back({{0, 0, 0}});
                } else {
                    ht_at_decision_pt.push_back({{0, 0, c.size() - 1}});
                }
            }
        }

        virtual literal getImpliedLiteral(clause_id i, literal assignment) {
            HTPointers ht = ht_at_decision_pt[i].back();
            bool modified = false;

            if (clauses[i][ht.head] == -assignment) {
                modified = true;
                while ((getAssignment(clauses[i][ht.head]) == FALSE) && (ht.head != ht.tail)) {
                    ht.head += 1;
                }  
            } else if (clauses[i][ht.tail] == -assignment) {
                modified = true;
                while ((getAssignment(clauses[i][ht.tail]) == FALSE) && (ht.head != ht.tail)) {
                    ht.tail -= 1;
                }
            }


            if (modified) {
                if (ht.decision_point < decision_points.size()) {
                    ht.decision_point++;
                    ht_at_decision_pt[i].push_back(ht);
                } else {
                    ht_at_decision_pt[i].back() = ht;
                }
            }

            if (ht.head == ht.tail) {
                return clauses[i][ht.head];
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

        virtual bool backtrack() {
            if (!this->Solver::backtrack()) {
                return false;
            }

            for (size_t i = 0; i < clauses.size(); i++) {
                while (ht_at_decision_pt[i].back().decision_point > decision_points.size()) {
                    ht_at_decision_pt[i].pop_back();
                }
            }

            return true;
        }

    private:
        struct HTPointers {
            size_t decision_point;
            lit_id head;
            lit_id tail;
        };

        std::vector<std::vector<HTPointers>> ht_at_decision_pt;
};
