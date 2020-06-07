// https://adventofcode.com/2019/day/14

#include <catch.hpp>
#include <queue>
#include "../day14-lib/day14-lib.hpp"

TEST_CASE("Puzzle input should be readable", "[part1][part2]") {
    std::string filename{ "../day14/day14-input.txt" };
    std::vector<std::string> puzzle_input(get_input(filename));
    REQUIRE(puzzle_input.size() == 59);
}

