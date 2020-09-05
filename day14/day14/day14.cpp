// https://adventofcode.com/2019/day/14

#include <iostream>
#include <gsl/gsl_assert>

#include "../day14-lib/day14-lib.hpp"

int main()
{
    const auto input{get_input("day14-input.txt")};
    const auto reactions{process_reactions(input)};

    const auto part1_answer{calculate_ore_required(reactions, 1LL)};

    std::cout << "part1_answer: " << part1_answer << "\n";
    Ensures(part1_answer == 399063);

    // Part 2

    long long fuel_amount{0LL};
    long long ore_required{0LL};
    while (ore_required <= 1'000'000'000'000)
    {
        ++fuel_amount;
        ore_required = calculate_ore_required(reactions, fuel_amount);
    }
    const auto part2_answer{fuel_amount - 1};
    std::cout << "part2_answer: " << fuel_amount - 1 << "\n";
    Ensures(part2_answer == 4215654);

    return 0;
}
