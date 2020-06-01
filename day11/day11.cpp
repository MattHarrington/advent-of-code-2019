// https://adventofcode.com/2019/day/11

#include <algorithm>
#include <cassert>
#include <fstream>
#include <gsl/gsl>
#include <iostream>
#include <map>
#include <queue>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

constexpr size_t PROGRAM_SIZE{ 1'000'000 };

enum class opcode {
    add = 1, multiply, input, output, jump_if_true, jump_if_false, less_than, equals, adjust_offset, halt = 99
};

enum class mode {
    position, immediate, relative
};

struct Program {
    std::vector<long long> intcodes;
    size_t ip;
    size_t offset;
    std::queue<int> input;
};

mode get_mode(long long modes) noexcept {
    if (modes % 10 == 0) return mode::position;
    else if (modes % 10 == 1) return mode::immediate;
    else return mode::relative;
}

/// <summary>Get a parameter</summary>
/// NB: not sure param tag is meant to be used this way:
/// <param name="lhs">True if parameter will be assigned to</param>
long long get_param(const Program& p, int param_num, mode mode, bool lhs = false) {
    if (lhs && mode == mode::relative) {
        return p.intcodes.at(p.ip + param_num) + p.offset;
    }
    else if (lhs) {
        return p.intcodes.at(p.ip + param_num);
    }
    else if (mode == mode::position) {
        return p.intcodes.at(p.intcodes.at(p.ip + param_num));
    }
    else if (mode == mode::immediate) {
        return p.intcodes.at(p.ip + param_num);
    }
    else {
        return p.intcodes.at(p.intcodes.at(p.ip + param_num) + p.offset);
    }
}

std::queue<long long> process(Program& p) {
    bool running{ true };
    std::queue<long long> outputs;
    while (running) {
        const opcode op{ p.intcodes.at(p.ip) < 100 ? static_cast<opcode>(p.intcodes.at(p.ip))
            : static_cast<opcode>(p.intcodes.at(p.ip) % 100) };

        // Get mode of parameters
        long long modes{ p.intcodes.at(p.ip) / 100 };
        const mode param1_mode{ get_mode(modes) };
        modes /= 10;
        const mode param2_mode{ get_mode(modes) };
        modes /= 10;
        const mode param3_mode{ get_mode(modes) };

        switch (op) {
        case opcode::add: {
            const auto param1{ get_param(p,1,param1_mode) };
            const auto param2{ get_param(p,2,param2_mode) };
            const auto param3{ get_param(p,3,param3_mode,true) };
            p.intcodes.at(param3) = param1 + param2;
            p.ip += 4;
            break;
        }
        case opcode::multiply: {
            const auto param1{ get_param(p,1,param1_mode) };
            const auto param2{ get_param(p,2,param2_mode) };
            const auto param3{ get_param(p,3,param3_mode,true) };
            p.intcodes.at(param3) = param1 * param2;
            p.ip += 4;
            break;
        }
        case opcode::input: {
            if (p.input.empty()) { running = false; break; }
            const auto param1{ get_param(p,1,param1_mode, true) };
            p.intcodes.at(param1) = p.input.front();
            p.input.pop();
            p.ip += 2;
            break;
        }
        case opcode::output: {
            const auto param1{ get_param(p,1,param1_mode) };
            outputs.push(param1);
            p.ip += 2;
            break;
        }
        case opcode::jump_if_true: {
            const auto param1{ get_param(p,1,param1_mode) };
            const auto param2{ get_param(p,2,param2_mode) };
            if (param1 != 0) {
                p.ip = param2;
            }
            else {
                p.ip += 3;
            }
            break;
        }
        case opcode::jump_if_false: {
            const auto param1{ get_param(p,1,param1_mode) };
            const auto param2{ get_param(p,2,param2_mode) };
            if (param1 == 0) {
                p.ip = param2;
            }
            else {
                p.ip += 3;
            }
            break;
        }
        case opcode::less_than: {
            const auto param1{ get_param(p,1,param1_mode) };
            const auto param2{ get_param(p,2,param2_mode) };
            const auto param3{ get_param(p,3,param3_mode,true) };
            if (param1 < param2) {
                p.intcodes.at(param3) = 1;
            }
            else {
                p.intcodes.at(param3) = 0;
            }
            p.ip += 4;
            break;
        }
        case opcode::equals: {
            const auto param1{ get_param(p,1,param1_mode) };
            const auto param2{ get_param(p,2,param2_mode) };
            const auto param3{ get_param(p,3,param3_mode,true) };
            if (param1 == param2) {
                p.intcodes.at(param3) = 1;
            }
            else {
                p.intcodes.at(param3) = 0;
            }
            p.ip += 4;
            break;
        }
        case opcode::adjust_offset: {
            const auto param1{ get_param(p,1,param1_mode) };
            p.offset += param1;
            p.ip += 2;
            break;
        }
        case opcode::halt: {
            running = false;
            break;
        }
        default:
            throw std::logic_error("Bad opcode");
        }
    }
    return outputs;
}

std::vector<long long> get_program(std::string filename) {
    std::vector<long long> program(PROGRAM_SIZE, 0);
    std::fstream in{ filename };
    if (!in) throw std::runtime_error("File not found");
    std::string value;
    size_t pos{ 0 };
    while (getline(in, value, ',')) {
        program.at(pos) = std::stoll(value);
        ++pos;
    }
    return program;
}

enum class color {
    black, white
};

enum class direction {
    left, right
};

enum class compass {
    north, east, south, west
};

using grid = std::vector<std::vector<int>>;

std::pair<size_t, grid> paint_hull(bool part2 = false) {
    constexpr int X_DIMENSION{ 140 };  // Just a guess
    constexpr int Y_DIMENSION{ 75 }; // Just a guess
    grid hull(Y_DIMENSION, std::vector<int>(X_DIMENSION, 0));
    int x{ X_DIMENSION / 2 };
    int y{ Y_DIMENSION / 2 };
    if (part2) hull.at(y).at(x) = 1; // Part 2 hull starts on white panel
    compass orientation{ compass::north };
    std::map<std::pair<int, int>, int> panels_painted;

    std::vector<long long> intcodes{ get_program("day11_input.txt") };
    assert(intcodes.size() == PROGRAM_SIZE);

    Program program{ intcodes,0,0,std::queue<int>{} };
    program.input.push(hull.at(y).at(x));
    auto part1_output{ process(program) };

    while (!part1_output.empty()) {
        const color color_to_paint{ static_cast<color>(part1_output.front()) };
        part1_output.pop();
        const direction direction_to_turn{ static_cast<direction>(part1_output.front()) };
        part1_output.pop();

        // Paint a panel
        if (color_to_paint == color::black) {
            hull.at(y).at(x) = 0;
        }
        else {
            hull.at(y).at(x) = 1;
        }
        panels_painted[std::make_pair(x, y)] += 1;

        // Rotate
        if (direction_to_turn == direction::left) {
            orientation = static_cast<compass>((static_cast<int>(orientation) + 3) % 4);
        }
        else {
            orientation = static_cast<compass>((static_cast<int>(orientation) + 1) % 4);
        }

        // Move
        switch (orientation) {
        case compass::north:
            --y;
            break;
        case compass::east:
            ++x;
            break;
        case compass::south:
            ++y;
            break;
        case compass::west:
            --x;
            break;
        default:
            throw std::invalid_argument("Invalid orientation");
        }

        // Provide new input to program and run another iteration
        program.input.push(hull.at(y).at(x));
        part1_output = process(program);
    }
    return std::make_pair(panels_painted.size(), hull);
}

void print_grid(const grid& grid) {
    for (const auto& row : grid) {
        std::for_each(begin(row), end(row), [](auto c) {if (c == 0) std::cout << " "; else std::cout << '*'; });
        std::cout << "\n";
    }
}

int main() {
    const size_t part1_answer{ paint_hull().first };
    std::cout << "part1_answer: " << part1_answer << "\n";
    assert(part1_answer == 1964);

    const grid part2_answer{ paint_hull(true).second };
    print_grid(part2_answer); // FKEKCFRK

    return 0;
}

