// https://adventofcode.com/2019/day/13

#include <gsl/gsl_assert>
#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include "day13-lib.hpp"

int part1(std::string(filename)) {
    const std::vector<long long> intcodes{ get_intcodes(filename) };
    Program program{ intcodes,0,0,std::queue<int>{} };
    std::queue<long long> part1_output{ process(program) };
    int block_tile_counter{ 0 };
    while (!part1_output.empty()) {
        part1_output.pop();
        part1_output.pop();
        const long long tile_id{ part1_output.front() };
        part1_output.pop();
        if (tile_id == 2) ++block_tile_counter;
    }
    return block_tile_counter;
}

struct Position {
    long long x;
    long long y;
};

long long part2(std::string(filename)) {
    std::vector<long long> intcodes{ get_intcodes(filename) };
    intcodes.at(0) = 2;
    Program program{ intcodes,0,0,std::queue<int>{} };
    program.input.push(0);
    Position ball{ -1,-1 };
    Position paddle{ -1,-1 };
    long long score{ 0 }; // Joystick in neutral position

    std::queue<long long> part1_output{ process(program) };
    long long num_blocks{ 236 }; // Result from part 1
    while (num_blocks > 0) {
        num_blocks = 0; // Reset
        while (!part1_output.empty()) {
            const long long x{ part1_output.front() };
            part1_output.pop();
            const long long y{ part1_output.front() };
            part1_output.pop();
            if (x == -1 && y == 0) {
                score = part1_output.front();
            }
            const long long tile_id{ part1_output.front() };
            if (tile_id == 2) {
                ++num_blocks; // num_blocks decreases round after round as game progresses
            }
            if (tile_id == 3) {
                paddle.x = x;
                paddle.y = y;
            }
            else if (tile_id == 4) {
                ball.x = x;
                ball.y = y;
            }
            part1_output.pop();
        }
        
        // Examine ball position and move paddle:
        if (ball.x > paddle.x) {
            program.input.push(1); // Move paddle right
        }
        else if (ball.x < paddle.x) {
            program.input.push(-1); // Move paddle left
        }
        else {
            program.input.push(0); // Don't move paddle
        }

        // Reset program and run another loop:
        program.ip = 0;
        program.offset = 0;
        part1_output = process(program);
    }
    return score;
}

int main() {
    const int part1_answer{ part1("day13-input.txt") };
    std::cout << "part1_answer: " << part1_answer << "\n";
    Ensures(part1_answer == 236);

    const long long part2_answer{ part2("day13-input.txt") };
    std::cout << "part2_answer: " << part2_answer << "\n";
    Ensures(part2_answer == 11040);
}

