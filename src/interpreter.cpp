#include "../include/ex_interpreter.hpp"
#include <iostream>
#include <ranges>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

std::vector<std::vector<std::string>> read_program(const char *file_name);
std::vector<std::string> split(const std::string);
void print_string_vector (const std::vector<std::string>);


int main(int argc, char *argv[])
{
    std::vector<std::vector<std::string>> lines = read_program(argv[1]);
    std::unordered_map<std::string, std::string> variables;
    std::stack<unsigned int> stack_last_while;
    std::stack<unsigned int> stack_last_endw;

    unsigned int pc = 0;

    //for (std::vector<std::string> line : lines) {
    while (pc < (unsigned int)(lines.size())) {
        const std::vector<std::string> line = lines[pc];

        // variable
        if (line[1] == "=") {
            const std::string variable = line[0];
            std::vector<std::string> expression (line.begin() + 2,
                                                 line.begin() + line.size());

            // replace variables for their values
            for (int i = 0; i < int(expression.size()); i++) {
                if (variables.contains(expression[i])) {
                    expression[i] = variables[expression[i]];
                }
            }

            const std::string value = std::to_string(ex_interpreter(expression));

            variables[variable] = value;
        }
        // while loop
        else if (line[0] == "while") {
            if (stack_last_while.empty() || stack_last_while.top() != pc) {
                stack_last_while.push(pc);
            }

            std::vector<std::string> expression (line.begin() + 1,
                                                 line.begin() + line.size());

            // replace variables for their values
            for (int i = 0; i < int(expression.size()); i++) {
                if (variables.contains(expression[i])) {
                    expression[i] = variables[expression[i]];
                }
            }

            const double value = ex_interpreter(expression);

            // condition false
            if (value == double(0)) {
                pc = stack_last_endw.top(); stack_last_endw.pop();
                stack_last_while.pop();
            }
        } // both stacks pop to not interfere with nested while loops
        else if (line[0] == "endw") {
            if (stack_last_endw.empty() || stack_last_endw.top() != pc) {
                stack_last_endw.push(pc);
            }

            pc = stack_last_while.top() - 1;
        }
        else if (line[0] == "if") {
            std::vector<std::string> expression (line.begin() + 1,
                                                 line.begin() + line.size());

            // replace variables for their values
            for (int i = 0; i < int(expression.size()); i++) {
                if (variables.contains(expression[i])) {
                    expression[i] = variables[expression[i]];
                }
            }

            const double value = ex_interpreter(expression);

            // condition false
            if (value == double(0)) {
                int i = pc;
                int counter_if = 1;
                while (lines[i][0] != "endif" && counter_if > 0) {
                    // to account for nested if statements
                    if (lines[i][0] == "if") {
                        counter_if++;
                    }
                    if (lines[i][0] == "endif") {
                        counter_if--;
                    }
                    i++;
                }

                pc = i;
            }
        }
        else if (line[0] == "endif") {
            /*nothing*/
        }
        // only print variable values
        else if (line[0] == "print") {
            for (int i = 1; i < int(line.size()); i++) {
                if (variables.contains(line[i])) {
                    std::cout << variables[line[i]] << " ";
                } else {
                    std::cout << line[i] << " ";
                }
            }

            std::cout << "\n";
        }



        /* Comments are indicated by the double slash (//) */

        pc++;
    }

    // Show variables and values
    std::cout << "VARIABLES" << "\n";
    for (auto it = variables.begin(); it != variables.end(); it++) {
        std::cout << it->first << " : " << it->second << "\n";
    }

    return 0;
}

std::vector<std::vector<std::string>> read_program(const char *file_name)
{
    std::ifstream file(file_name);
    std::string s;
    std::vector<std::vector<std::string>> lines;

    while (std::getline(file, s)) {
        const std::vector<std::string> line = split(s);

        if (line.size() > 0) {
            lines.push_back(line);
        }
    }

    return lines;
}

std::vector<std::string> split(const std::string s)
{
    /*
        Returns a vector of strings from the original string, spliting
        the words by space (' ') or tab ('\t').
    */
    bool is_empty_string = true;
    int  start = 0;
    std::vector<std::string> words;

    for (int i = 0; i < int(s.size()); i++) {
        if (s[i] == ' ' || s[i] == '\t') {
            if (start != i) {
                words.push_back(s.substr(start, i-start));
            }

            start = i + 1;
        } else {
            is_empty_string = false;
        }
    }

    if (!is_empty_string && start < int(s.size())) {
        words.push_back(s.substr(start, int(s.size()) - start));
    }

    return words;
}

void print_string_vector (const std::vector<std::string> ws) {
    /*
        Print and format the elements of a vector of strings.
        For test purposes.
    */
    std::string s = "";

    s += "[ ";

    for (std::string w : ws) {
        s += "\"" + w + "\"" + ", ";
    }

    if (s.size() > 2) {
        s = s.substr(0, s.size()-2);
    }

    s += " ]";

    std::cout << s << "\n";
}























