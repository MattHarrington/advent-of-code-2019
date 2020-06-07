// https://adventofcode.com/2019/day/14

#include <fstream>
#include <stdexcept>
#include "day14-lib.hpp"

std::vector<std::string> get_input(const std::string& filename) {
    std::vector<std::string> output;
    std::fstream in{ filename };
    if (!in) throw std::runtime_error("File not found");
    std::string line;
    while (getline(in, line)) {
        output.push_back(line);
    }
    return output;
}

