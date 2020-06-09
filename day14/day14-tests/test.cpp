#include "pch.h"

TEST(TestCaseName, TestName) {
    EXPECT_EQ(1, 1);
    EXPECT_TRUE(true);
}

TEST(GetInput, PuzzleInputIsReadable) {
    std::vector<std::string> puzzle_input{ get_input("../../day14/day14/day14-input.txt") };
    EXPECT_EQ(puzzle_input.size(), 59) << "Puzzle length incorrect";
}

