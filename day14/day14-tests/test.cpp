#include "pch.h"

TEST(GetInput, PuzzleInputIsReadable) {
    std::vector<std::string> puzzle_input{ get_input("../../day14/day14/day14-input.txt") };
    EXPECT_EQ(puzzle_input.size(), 59) << "Puzzle length incorrect";
}

TEST(ProcessInput, ReactionsLookGood) {
    std::vector<std::string> puzzle_input{ get_input("../../day14/day14/day14-input.txt") };
    const auto reactions{ process_reactions(puzzle_input) };
    EXPECT_EQ(reactions.size(), 59) << "Reaction map length incorrect";
}

TEST(Part1, Sample1Works)
{
    const std::vector<std::string> puzzle_input{ get_input("../../day14/day14/day14-sample-input1.txt") };
    const auto reactions{ process_reactions(puzzle_input) };
    const auto part1_answer{ calculate_required_fuel(reactions) };
    EXPECT_EQ(part1_answer, 31) << "Sample 1 fails";
}

TEST(Part1, Sample2Works)
{
    const std::vector<std::string> puzzle_input{ get_input("../../day14/day14/day14-sample-input2.txt") };
    const auto reactions{ process_reactions(puzzle_input) };
    const auto part1_answer{ calculate_required_fuel(reactions) };
    EXPECT_EQ(part1_answer, 165) << "Sample 2 fails";
}

TEST(Part1, Sample3Works)
{
    const std::vector<std::string> puzzle_input{ get_input("../../day14/day14/day14-sample-input3.txt") };
    const auto reactions{ process_reactions(puzzle_input) };
    const auto part1_answer{ calculate_required_fuel(reactions) };
    EXPECT_EQ(part1_answer, 13312) << "Sample 3 fails";
}

TEST(Part1, Sample4Works)
{
    const std::vector<std::string> puzzle_input{ get_input("../../day14/day14/day14-sample-input4.txt") };
    const auto reactions{ process_reactions(puzzle_input) };
    const auto part1_answer{ calculate_required_fuel(reactions) };
    EXPECT_EQ(part1_answer, 180697) << "Sample 4 fails";
}

TEST(Part1, Sample5Works)
{
    const std::vector<std::string> puzzle_input{ get_input("../../day14/day14/day14-sample-input5.txt") };
    const auto reactions{ process_reactions(puzzle_input) };
    const auto part1_answer{ calculate_required_fuel(reactions) };
    EXPECT_EQ(part1_answer, 2210736) << "Sample 5 fails";
}

