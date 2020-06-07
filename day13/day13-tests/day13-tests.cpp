// https://adventofcode.com/2019/day/13

#include <catch.hpp>
#include <queue>
#include "day13-lib.hpp"

TEST_CASE("puzzle input should be readable", "[part1][part2]") {
    std::vector<long long> const intcodes{ get_intcodes("../day13/day13-input.txt") };
    REQUIRE(intcodes.size() == 1'000'000);
}

TEST_CASE("puzzle input should generate 2268 outputs", "[part1]") {
    std::vector<long long> intcodes{ get_intcodes("../day13/day13-input.txt") };
    Program program{ intcodes,0,0,std::queue<int>{} };
    const std::queue<long long> part1_output{ process(program) };
    REQUIRE(part1_output.size() == 2268);
}

