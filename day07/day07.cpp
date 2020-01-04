// https://adventofcode.com/2019/day/7

#include <algorithm>
#include <cassert>
#include <iostream>
#include <queue>
#include <stdexcept>
#include <vector>

enum class opcode {
	add = 1, multiply, input, output, jump_if_true, jump_if_false, less_than, equals, halt = 99
};

enum class mode {
	position, immediate
};

struct Program {
	std::vector<int> intcodes;
	size_t ip;
	std::queue<int> input;
};

std::queue<int> process(Program& p) {
	bool running{ true };
	std::queue<int> outputs;
	while (running) {
		int modes{ p.intcodes.at(p.ip) / 100 };
		const mode param1_mode = modes % 10 == 0 ? mode::position : mode::immediate;
		modes /= 10;
		const mode param2_mode = modes % 10 == 0 ? mode::position : mode::immediate;

		const opcode op{ p.intcodes.at(p.ip) < 100 ? static_cast<opcode>(p.intcodes.at(p.ip))
			: static_cast<opcode>(p.intcodes.at(p.ip) % 100) };

		switch (op) {
		case opcode::add: {
			auto param1{ param1_mode == mode::position ? p.intcodes.at(p.intcodes.at(p.ip + 1)) : p.intcodes.at(p.ip + 1) };
			auto param2{ param2_mode == mode::position ? p.intcodes.at(p.intcodes.at(p.ip + 2)) : p.intcodes.at(p.ip + 2) };
			auto param3{ p.intcodes.at(p.ip + 3) };
			p.intcodes.at(param3) = param1 + param2;
			p.ip += 4;
			break;
		}
		case opcode::multiply: {
			auto param1{ param1_mode == mode::position ? p.intcodes.at(p.intcodes.at(p.ip + 1)) : p.intcodes.at(p.ip + 1) };
			auto param2{ param2_mode == mode::position ? p.intcodes.at(p.intcodes.at(p.ip + 2)) : p.intcodes.at(p.ip + 2) };
			auto param3{ p.intcodes.at(p.ip + 3) };
			p.intcodes.at(param3) = param1 * param2;
			p.ip += 4;
			break;
		}
		case opcode::input: {
			if (p.input.empty()) { running = false; break; }
			auto param1{ p.intcodes.at(p.ip + 1) };
			p.intcodes.at(param1) = p.input.front();
			p.input.pop();
			p.ip += 2;
			break;
		}
		case opcode::output: {
			auto param1{ param1_mode == mode::position ? p.intcodes.at(p.intcodes.at(p.ip + 1)) : p.intcodes.at(p.ip + 1) };
			outputs.push(param1);
			p.ip += 2;
			break;
		}
		case opcode::jump_if_true: {
			auto param1{ param1_mode == mode::position ? p.intcodes.at(p.intcodes.at(p.ip + 1)) : p.intcodes.at(p.ip + 1) };
			auto param2{ param2_mode == mode::position ? p.intcodes.at(p.intcodes.at(p.ip + 2)) : p.intcodes.at(p.ip + 2) };
			if (param1 != 0) {
				p.ip = param2;
			}
			else {
				p.ip += 3;
			}
			break;
		}
		case opcode::jump_if_false: {
			auto param1{ param1_mode == mode::position ? p.intcodes.at(p.intcodes.at(p.ip + 1)) : p.intcodes.at(p.ip + 1) };
			auto param2{ param2_mode == mode::position ? p.intcodes.at(p.intcodes.at(p.ip + 2)) : p.intcodes.at(p.ip + 2) };
			if (param1 == 0) {
				p.ip = param2;
			}
			else {
				p.ip += 3;
			}
			break;
		}
		case opcode::less_than: {
			auto param1{ param1_mode == mode::position ? p.intcodes.at(p.intcodes.at(p.ip + 1)) : p.intcodes.at(p.ip + 1) };
			auto param2{ param2_mode == mode::position ? p.intcodes.at(p.intcodes.at(p.ip + 2)) : p.intcodes.at(p.ip + 2) };
			auto param3{ p.intcodes.at(p.ip + 3) };
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
			auto param1{ param1_mode == mode::position ? p.intcodes.at(p.intcodes.at(p.ip + 1)) : p.intcodes.at(p.ip + 1) };
			auto param2{ param2_mode == mode::position ? p.intcodes.at(p.intcodes.at(p.ip + 2)) : p.intcodes.at(p.ip + 2) };
			auto param3{ p.intcodes.at(p.ip + 3) };
			if (param1 == param2) {
				p.intcodes.at(param3) = 1;
			}
			else {
				p.intcodes.at(param3) = 0;
			}
			p.ip += 4;
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

int part1(Program p, std::vector<int> phase_settings) {
	std::queue<int> input;
	std::vector<int> outputs;
	do {
		Program ampA{ p };
		Program ampB{ p };
		Program ampC{ p };
		Program ampD{ p };
		Program ampE{ p };

		ampA.input.push(phase_settings.at(0));
		ampB.input.push(phase_settings.at(1));
		ampC.input.push(phase_settings.at(2));
		ampD.input.push(phase_settings.at(3));
		ampE.input.push(phase_settings.at(4));

		ampA.input.push(0);
		std::queue<int> ampA_output{ process(ampA) };

		ampB.input.push(ampA_output.front());
		ampA_output.pop();
		std::queue<int> ampB_output{ process(ampB) };

		ampC.input.push(ampB_output.front());
		ampB_output.pop();
		std::queue<int> ampC_output{ process(ampC) };

		ampD.input.push(ampC_output.front());
		ampC_output.pop();
		std::queue<int> ampD_output{ process(ampD) };

		ampE.input.push(ampD_output.front());
		ampD_output.pop();
		std::queue<int> ampE_output{ process(ampE) };

		outputs.push_back(ampE_output.front());
	} while (std::next_permutation(begin(phase_settings), end(phase_settings)));

	return *std::max_element(begin(outputs), end(outputs));
}

int part2(const std::vector<int>& program, std::vector<int> phase_settings) {
	std::vector<int> outputs;
	do {
		Program ampA{ program, 0, std::queue<int>{} };
		Program ampB{ program, 0, std::queue<int>{} };
		Program ampC{ program, 0, std::queue<int>{} };
		Program ampD{ program, 0, std::queue<int>{} };
		Program ampE{ program, 0, std::queue<int>{} };

		ampA.input.push(phase_settings.at(0));
		ampB.input.push(phase_settings.at(1));
		ampC.input.push(phase_settings.at(2));
		ampD.input.push(phase_settings.at(3));
		ampE.input.push(phase_settings.at(4));

		ampA.input.push(0); // Initial input

		do {
			// Amp A
			std::queue<int> ampA_output = process(ampA);
			while (!ampA_output.empty()) {
				// TODO: this is hacky.  Look at std::deque instead.
				ampB.input.push(ampA_output.front());
				ampA_output.pop();
			}

			// Amp B
			std::queue<int> ampB_output{ process(ampB) };
			while (!ampB_output.empty()) {
				ampC.input.push(ampB_output.front());
				ampB_output.pop();
			}

			// Amp C
			std::queue<int> ampC_output{ process(ampC) };
			while (!ampC_output.empty()) {
				ampD.input.push(ampC_output.front());
				ampC_output.pop();
			}

			// Amp D
			std::queue<int> ampD_output{ process(ampD) };
			while (!ampD_output.empty()) {
				ampE.input.push(ampD_output.front());
				ampD_output.pop();
			}

			// Amp E
			std::queue<int> ampE_output = process(ampE);
			while (!ampE_output.empty()) {
				ampA.input.push(ampE_output.front());
				ampE_output.pop();
			}

		} while (static_cast<opcode>(ampE.intcodes.at(ampE.ip)) != opcode::halt);

		outputs.push_back(ampA.input.front());
	} while (std::next_permutation(begin(phase_settings), end(phase_settings)));

	return *std::max_element(begin(outputs), end(outputs));
}

int main() {
	std::vector<int> program{ 3,8,1001,8,10,8,105,1,0,0,21,34,59,68,89,102,183,264,345,426,99999,3,9,102,5,9,9,1001,
		9,5,9,4,9,99,3,9,101,3,9,9,1002,9,5,9,101,5,9,9,1002,9,3,9,1001,9,5,9,4,9,99,3,9,101,5,9,9,4,9,99,3,9,102,4,
		9,9,101,3,9,9,102,5,9,9,101,4,9,9,4,9,99,3,9,1002,9,5,9,1001,9,2,9,4,9,99,3,9,1002,9,2,9,4,9,3,9,101,2,9,9,
		4,9,3,9,1001,9,2,9,4,9,3,9,101,1,9,9,4,9,3,9,102,2,9,9,4,9,3,9,1001,9,2,9,4,9,3,9,1001,9,2,9,4,9,3,9,1001,9,
		2,9,4,9,3,9,1001,9,2,9,4,9,3,9,102,2,9,9,4,9,99,3,9,1001,9,1,9,4,9,3,9,102,2,9,9,4,9,3,9,102,2,9,9,4,9,3,9,
		101,1,9,9,4,9,3,9,101,1,9,9,4,9,3,9,102,2,9,9,4,9,3,9,102,2,9,9,4,9,3,9,101,1,9,9,4,9,3,9,1001,9,2,9,4,9,3,
		9,1001,9,2,9,4,9,99,3,9,1002,9,2,9,4,9,3,9,102,2,9,9,4,9,3,9,102,2,9,9,4,9,3,9,1001,9,2,9,4,9,3,9,1001,9,2,
		9,4,9,3,9,102,2,9,9,4,9,3,9,101,1,9,9,4,9,3,9,1001,9,1,9,4,9,3,9,1002,9,2,9,4,9,3,9,102,2,9,9,4,9,99,3,9,
		101,1,9,9,4,9,3,9,1002,9,2,9,4,9,3,9,102,2,9,9,4,9,3,9,1002,9,2,9,4,9,3,9,102,2,9,9,4,9,3,9,1002,9,2,9,4,9,
		3,9,102,2,9,9,4,9,3,9,1002,9,2,9,4,9,3,9,101,1,9,9,4,9,3,9,101,2,9,9,4,9,99,3,9,1001,9,1,9,4,9,3,9,1001,9,
		2,9,4,9,3,9,101,1,9,9,4,9,3,9,102,2,9,9,4,9,3,9,1001,9,2,9,4,9,3,9,1002,9,2,9,4,9,3,9,101,1,9,9,4,9,3,9,
		1001,9,1,9,4,9,3,9,1001,9,2,9,4,9,3,9,1002,9,2,9,4,9,99 };
	std::vector<int> sample1_part2_program{ 3,26,1001,26,-4,26,3,27,1002,27,2,27,1,27,26,
											27,4,27,1001,28,-1,28,1005,28,6,99,0,0,5 };
	std::vector<int> sample2_part2_program{ 3,52,1001,52,-5,52,3,53,1,52,56,54,1007,54,5,55,1005,55,26,1001,54,
											-5,54,1105,1,12,1,53,54,53,1008,54,0,55,1001,55,1,55,2,53,55,53,4,
											53,1001,56,-1,56,1005,56,6,99,0,0,0,0,10 };

	const int part1_answer{ part1(Program{program,0,std::queue<int>()}, std::vector<int>{0,1,2,3,4}) };
	std::cout << "part1_answer: " << part1_answer << "\n";
	assert(part1_answer == 70597);

	const int sample1_part2_answer{ part2(sample1_part2_program, std::vector<int>{5,6,7,8,9}) };
	assert(sample1_part2_answer == 139629729);

	const int sample2_part2_answer{ part2(sample2_part2_program, std::vector<int>{5,6,7,8,9}) };
	assert(sample2_part2_answer == 18216);

	const int part2_answer{ part2(program, std::vector<int>{5,6,7,8,9}) };
	std::cout << "part2_answer: " << part2_answer << "\n";
	assert(part2_answer == 30872528);

	return 0;
}

