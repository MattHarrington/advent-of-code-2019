// https://adventofcode.com/2019/day/14

#include <fstream>
#include <regex>
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

std::map<std::string, std::deque<Reactant>> process_reactions(std::vector<std::string> input) {
    // Parse element in vector with regex
    // create queue
    // 12 HKGWZ, 1 GPVTF, 8 PSHF => 9 QDVJ
    std::map<std::string, std::deque<Reactant>> reactions;
    const std::regex rx{ R"((\d+) ([A-Z]+))" };
    for (auto& reaction : input) {
        std::smatch sm;
        std::deque<Reactant> q;
        while (std::regex_search(reaction, sm, rx)) {
            q.emplace_back(Reactant{ sm[2], std::stoi(sm[1]) });
            reaction = sm.suffix();
        }
        Reactant product{ q.back() };
        reactions[product.name] = q;
    }
    return reactions;
}

auto calculate_required_fuel(const std::map<std::string, std::deque<Reactant>>& reactions) -> int
{
    std::deque<Reactant> q{ reactions.at("FUEL") };
    q.pop_back(); // Remove "FUEL", since it's the product
    std::map<std::string, int> ore_map; // Keeps track of # of reactants which form ORE

    while (!q.empty()) {
        Reactant r{ q.front() };
        q.pop_front();
        auto reaction{ reactions.at(r.name) }; // Reaction which produces r
        //int multiple{ r.quantity / reaction.back().quantity };
        int multiple{ 0 };
        if (r.quantity % reaction.back().quantity == 0)
        {
            multiple = r.quantity / reaction.back().quantity;
        }
        else
        {
            multiple = (r.quantity / reaction.back().quantity) + 1;
        }

        if (reaction.front().name == "ORE") {
            ore_map[r.name] += r.quantity;
        }
        else while (reaction.size() > 1)
        {
            q.emplace_back(Reactant{ reaction.front().name, reaction.front().quantity * multiple });
            reaction.pop_front();
        }

    }

    // Process ore_map
    int ore_count{ 0 };
    for (const auto& [name, quantity] : ore_map)
    {
        int multiplier{ 0 };
        auto rxn{ reactions.at(name) };
        if (quantity % rxn.back().quantity == 0)
        {
            multiplier = quantity / rxn.back().quantity;
        }
        else
        {
            multiplier = (quantity / rxn.back().quantity) + 1;
        }
        ore_count += rxn.front().quantity * multiplier;
    }

    return ore_count;
}

