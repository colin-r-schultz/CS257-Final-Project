#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

typedef int literal;
typedef std::vector<literal> clause;

int parse(const std::string& file_name, std::vector<clause>& clauses) {
    clauses.clear();
    std::ifstream cnf_file(file_name);
    std::string line;
    int num_vars = -1;

    while (std::getline(cnf_file, line)) {
        if (line[0] == 'c') {
            continue;
        }
        std::stringstream ss(line);
        std::string header;

        if (line[0] == 'p') {
            while (getline(ss, header, ' ')) {
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

    return num_vars;
}

void print_clauses(const std::vector<clause>& clauses) {
    for (const clause c : clauses) {
        std::cout << "clause ";
        for (const literal lit : c) {
            std::cout << lit << " ";
        }
        std::cout << std::endl;
    }
}