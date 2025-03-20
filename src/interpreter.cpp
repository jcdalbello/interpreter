#include <iostream>
#include <ranges>
#include <fstream>
#include <string>
#include <vector>

std::vector<std::string> split(const std::string);
void print_string_vector (const std::vector<std::string>);


int main(int argc, char *argv[])
{
    std::ifstream file(argv[1]);
    std::string s;
    std::vector<std::vector<std::string>> lines;

    while (std::getline(file, s)) {
        const std::vector<std::string> line = split(s);
        if (line.size() > 0) {
            lines.push_back(line);
        }
    }

    for (std::vector<std::string> line : lines) {

    }

    return 0;
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























