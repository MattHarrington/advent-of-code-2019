// https://adventofcode.com/2019/day/14

#include "day14-lib.hpp"

#include <algorithm>
#include <fstream>
#include <regex>
#include <stdexcept>

std::vector<std::string> get_input(const std::string& filename)
{
    std::vector<std::string> output;
    std::fstream in{filename};
    if (!in) throw std::runtime_error("File not found");
    std::string line;
    while (getline(in, line))
    {
        output.push_back(line);
    }
    return output;
}

std::map<std::string, std::deque<Reactant>> process_reactions(std::vector<std::string> input)
{
    // Parse element in vector with regex
    // create queue
    // 12 HKGWZ, 1 GPVTF, 8 PSHF => 9 QDVJ
    std::map<std::string, std::deque<Reactant>> reactions;
    const std::regex rx{R"((\d+) ([A-Z]+))"};
    for (auto& reaction : input)
    {
        std::smatch sm;
        std::deque<Reactant> q;
        while (std::regex_search(reaction, sm, rx))
        {
            q.emplace_back(Reactant{sm[2], std::stoi(sm[1])});
            reaction = sm.suffix();
        }
        Reactant product{q.back()};
        reactions[product.name] = q;
    }
    return reactions;
}

// Kudos to tcbrindle for the tips.
// https://github.com/tcbrindle/advent_of_code_2019/blob/master/dec14/main.cpp
long long calculate_ore_required(const std::map<std::string, std::deque<Reactant>>& reaction_map,
                                 const long long fuel_amount)
{
    long long ore_required{0};
    std::map<std::string, long long> quantities;

    std::deque<Reactant> reactants_to_make{{"FUEL", fuel_amount}};

    while (!reactants_to_make.empty())
    {
        Reactant required_reactant{reactants_to_make.front()};
        reactants_to_make.pop_front();

        if (required_reactant.name == "ORE")
        {
            quantities[required_reactant.name] += required_reactant.quantity;
            ore_required += required_reactant.quantity;
            continue;
        }

        const auto used_from_stock{std::min(quantities[required_reactant.name], required_reactant.quantity)};
        quantities[required_reactant.name] -= used_from_stock;
        required_reactant.quantity -= used_from_stock;

        if (required_reactant.quantity == 0)
        {
            // We had enough in stock to make it
            continue;
        }

        const auto recipe_quantity{reaction_map.at(required_reactant.name).back().quantity};

        // Calculate multiple: how many times we need to make each recipe
        const auto multiple{
            required_reactant.quantity / recipe_quantity + (required_reactant.quantity % recipe_quantity != 0)
        };

        // Save surplus
        quantities[required_reactant.name] += recipe_quantity * multiple - required_reactant.quantity;

        // Add reactants to queue
        std::deque<Reactant> reactants_to_add{reaction_map.at(required_reactant.name)};
        while (!reactants_to_add.empty())
        {
            Reactant next_reactant{reactants_to_add.front()};
            if (next_reactant.name != required_reactant.name)
            {
                next_reactant.quantity *= multiple;
                reactants_to_make.push_back(next_reactant);
            }
            reactants_to_add.pop_front();
        }
    }

    return ore_required;
}
