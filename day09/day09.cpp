// https://adventofcode.com/2019/day/9

#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <queue>
#include <stdexcept>
#include <string>
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
	int offset;
	std::queue<int> input;
};

mode get_mode(long long modes) {
	if (modes % 10 == 0) return mode::position;
	else if (modes % 10 == 1) return mode::immediate;
	else return mode::relative;
}

long long get_param(Program& p, int param_num, mode mode, bool lhs = false) {
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
			auto param1{ get_param(p,1,param1_mode) };
			auto param2{ get_param(p,2,param2_mode) };
			auto param3{ get_param(p,3,param3_mode,true) };
			p.intcodes.at(param3) = param1 + param2;
			p.ip += 4;
			break;
		}
		case opcode::multiply: {
			auto param1{ get_param(p,1,param1_mode) };
			auto param2{ get_param(p,2,param2_mode) };
			auto param3{ get_param(p,3,param3_mode,true) };
			p.intcodes.at(param3) = param1 * param2;
			p.ip += 4;
			break;
		}
		case opcode::input: {
			if (p.input.empty()) { running = false; break; }
			auto param1{ get_param(p,1,param1_mode, true) };
			p.intcodes.at(param1) = p.input.front();
			p.input.pop();
			p.ip += 2;
			break;
		}
		case opcode::output: {
			auto param1{ get_param(p,1,param1_mode) };
			outputs.push(param1);
			p.ip += 2;
			break;
		}
		case opcode::jump_if_true: {
			auto param1{ get_param(p,1,param1_mode) };
			auto param2{ get_param(p,2,param2_mode) };
			if (param1 != 0) {
				p.ip = param2;
			}
			else {
				p.ip += 3;
			}
			break;
		}
		case opcode::jump_if_false: {
			auto param1{ get_param(p,1,param1_mode) };
			auto param2{ get_param(p,2,param2_mode) };
			if (param1 == 0) {
				p.ip = param2;
			}
			else {
				p.ip += 3;
			}
			break;
		}
		case opcode::less_than: {
			auto param1{ get_param(p,1,param1_mode) };
			auto param2{ get_param(p,2,param2_mode) };
			auto param3{ get_param(p,3,param3_mode,true) };
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
			auto param1{ get_param(p,1,param1_mode) };
			auto param2{ get_param(p,2,param2_mode) };
			auto param3{ get_param(p,3,param3_mode,true) };
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
			auto param1{ get_param(p,1,param1_mode) };
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

int main() {
	std::vector<long long> example1_intcodes{ 109,1,204,-1,1001,100,1,100,1008,100,16,101,1006,101,0,99 };
	for (size_t i{ 0 }; i < PROGRAM_SIZE; ++i) example1_intcodes.push_back(0);

	std::vector<long long> example2_intcodes{ 1102,34915192,34915192,7,4,7,99,0 };
	for (size_t i{ 0 }; i < PROGRAM_SIZE; ++i) example2_intcodes.push_back(0);

	std::vector<long long> example3_intcodes{ 104,1125899906842624,99 };
	for (size_t i{ 0 }; i < PROGRAM_SIZE; ++i) example3_intcodes.push_back(0);

	std::vector<long long> intcodes{ get_program("day09_input.txt") };
	assert(intcodes.size() == PROGRAM_SIZE);

	Program example1_program{ example1_intcodes };
	auto example1_output{ process(example1_program) };

	Program example2_program{ example2_intcodes };
	auto example2_output{ process(example2_program) };

	Program example3_program{ example3_intcodes };
	auto example3_output{ process(example3_program) };

	Program part1_program{ intcodes };
	part1_program.input.push(1);
	const auto part1_output{ process(part1_program) };
	const auto part1_answer{ part1_output.front() };
	std::cout << "part1_answer: " << part1_answer << "\n";
	assert(part1_answer == 3409270027);

	Program part2_program{ intcodes };
	part2_program.input.push(2);
	const auto part2_output{ process(part2_program) };
	const auto part2_answer{ part2_output.front() };
	std::cout << "part2_answer: " << part2_answer << "\n";
	assert(part2_answer == 82760);

	return 0;
}

