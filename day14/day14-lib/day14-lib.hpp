// https://adventofcode.com/2019/day/14

#ifndef DAY14_LIB_HPP
#define DAY14_LIB_HPP

#include <map>
#include <queue>
#include <string>
#include <vector>

struct Reactant {
    std::string name;
    int quantity;
};

std::vector<std::string> get_input(const std::string&);

std::map<std::string, std::queue<Reactant>> process_reactions(std::vector<std::string>);

auto calculate_required_fuel(const std::map<std::string, std::queue<Reactant>>&) -> int;

#endif

