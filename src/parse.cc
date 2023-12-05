#include <string>
#include <fstream>
#include <vector>
#include <sstream>

typedef int literal;
typedef std::vector<literal> clause;

class Parser {
    public:
        Parser(std::string file_name) {
            std::ifstream cnf_file (file_name);
            std::string line;

            while (std::getline(cnf_file, line)) {
                if (line[0] == 'c') {
                    continue;
                }
                std::stringstream ss(line);
                std::string header;

                if (line[0] == 'p') {
                    while(getline(ss, header, ' ')) {
                        if (header == "p" || header == "cnf") {
                            continue;
                        }

                        num_vars = stoi(header);
                        break;
                    }
                    continue;
                }

                clause curr = {};
                std::string lit;
                while (getline(ss, lit, ' ')) {
                    if (lit != "0") {
                        curr.push_back(stoi(lit));
                    }
                }
                clauses.push_back(curr);
            }
        }
        
        std::vector<clause> get_clauses() {
            return clauses;
        }

        size_t get_num_vars() {
            return num_vars;
        }

        void print_file() {
            for (const clause c : clauses) {
                std::cout << "clause ";
                for (const literal lit : c) {
                    std::cout << lit << " ";
                }
                std::cout << std::endl;
            }
        }

    private:
        std::vector<clause> clauses;
        size_t num_vars;
};