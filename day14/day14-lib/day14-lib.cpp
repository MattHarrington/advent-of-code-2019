// https://adventofcode.com/2019/day/14

#include <fstream>
#include <numeric>
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

std::map<std::string, std::queue<Reactant>> process_reactions(std::vector<std::string> input) {
    // Parse element in vector with regex
    // create queue
    // 12 HKGWZ, 1 GPVTF, 8 PSHF => 9 QDVJ
    std::map<std::string, std::queue<Reactant>> reactions;
    const std::regex rx{ R"((\d+) ([A-Z]+))" };
    for (auto& reaction : input) {
        std::smatch sm;
        std::queue<Reactant> q;
        while (std::regex_search(reaction, sm, rx)) {
            q.emplace(Reactant{ sm[2], std::stoi(sm[1]) });
            reaction = sm.suffix();
        }
        Reactant product{ q.back() };
        reactions[product.name] = q;
    }
    return reactions;
}

auto calculate_required_fuel(const std::map<std::string, std::queue<Reactant>>& reactions) -> int
{
    // Pass reactions by value so a copy is made
    std::queue<Reactant> q{reactions.at("FUEL")};
    std::map<std::string, int> ore_map;

    // Start with the reaction for FUEL
    //while (reactions.at("FUEL").size() > 1) { // Skips last element in queue, which is product of reaction
    //    q.push(reactions.at("FUEL").front());
    //    reactions.at("FUEL").pop();
    //}

    // Pop element off queue
    // Look up reaction for that element
    // if reaction is for ORE, then what?
    // multiple = LCM of what was popped off and reaction
    // add reactants to queue after multiplying by multiple
    while (!q.empty()) {
        Reactant r{ q.front() };
        q.pop();
        auto reaction{ reactions.at(r.name) };
        //const int multiple{ std::lcm(r.quantity, reaction.back().quantity) };
        int multiple{ 0 };
        if (r.quantity % reaction.back().quantity == 0)
        {
            multiple = r.quantity / reaction.back().quantity;
        }
        else
        {
            multiple = (r.quantity / reaction.back().quantity) + 1;
        }

        if (reaction.front().name == "ORE")
        {
            reaction.pop();
            ore_map[r.name] += r.quantity;
        }
        else while (reaction.size() > 1)
        {
            q.emplace(Reactant{ reaction.front().name, reaction.front().quantity * multiple });
            reaction.pop();
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

