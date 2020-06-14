// https://adventofcode.com/2019/day/14

#include <iostream>
#include "../day14-lib/day14-lib.hpp"

int main()
{
    std::cout << "Hello World!\n";
    const auto input{ get_input("day14-sample-input4.txt") };
    const auto reactions{ process_reactions(input) };
    const auto part1_answer{ calculate_required_fuel(reactions) };
    std::cout << "part1_answer: " << part1_answer << "\n";
    return 0;
}
// 3590460450 too high
// 625138 too high

