#include "../include/ex_interpreter.hpp"
#include <vector>
#include <string>
#include <stack>
#include <math.h>

/*
a b op
ej:
    1 2 +           (1+2)
    9.3 4.1 -       (9.3-4.1)
    10 2.1 3.06 + / (10/(2.1+3.06))
*/

double ex_interpreter(const std::vector<std::string> params)
{
    std::stack<double> st;

    for (std::string param : params) {
        if (is_double(param)) {
            st.push(std::stod(param));
        } else {
            const double b = st.top(); st.pop();
            const double a = st.top(); st.pop();
            st.push(operation(a, b, param));
        }
    }

    const double result = st.top(); st.pop();
    return result;
}

bool is_double(const std::string s)
{
    int points = 0;
    for (char c : s) {
        if (!isdigit(c) && c != '.') { return false; }
        if (c == '.') { points++; }
    }

    if (points > 1) { return false; }

    return true;
}

double operation(const double a, const double b, const std::string param)
{
    if (param == "+") { return a+b; }
    if (param == "-") { return a-b; }
    if (param == "*") { return a*b; }
    if (param == "/") { return b != 0 ? a/b : NAN; }
    if (param == "^") { return std::pow(a, b); }

    return double(0);
}














