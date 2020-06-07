// https://adventofcode.com/2019/day/13

#include <fstream>
#include <queue>
#include <stdexcept>
#include <string>
#include <vector>
#include "day13-lib.hpp"

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

std::vector<long long> get_intcodes(std::string filename) {
    std::vector<long long> intcodes(PROGRAM_SIZE, 0);
    std::fstream in{ filename };
    if (!in) throw std::runtime_error("File not found");
    std::string value;
    size_t pos{ 0 };
    while (getline(in, value, ',')) {
        intcodes.at(pos) = std::stoll(value);
        ++pos;
    }
    return intcodes;
}

