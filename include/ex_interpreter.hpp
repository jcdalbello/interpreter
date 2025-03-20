#ifndef EX_INTERPRETER_H
#define EX_INTERPRETER_H

#include <vector>
#include <string>
#include <stack>

double ex_interpreter(const std::vector<std::string>);
bool is_double(const std::string);
double operation(double, double, std::string);

#endif
