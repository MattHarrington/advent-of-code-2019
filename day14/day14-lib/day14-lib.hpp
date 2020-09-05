// https://adventofcode.com/2019/day/14

#pragma once

#include <deque>
#include <map>
#include <string>
#include <vector>

struct Reactant
{
    std::string name;
    long long quantity;
};

std::vector<std::string> get_input(const std::string&);

std::map<std::string, std::deque<Reactant>> process_reactions(std::vector<std::string>);

long long calculate_ore_required(const std::map<std::string, std::deque<Reactant>>&, const long long);
