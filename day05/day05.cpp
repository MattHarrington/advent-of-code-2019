// https://adventofcode.com/2019/day/5

#include <cassert>
#include <iostream>
#include <stdexcept>
#include <vector>

enum class opcode {
	add = 1, multiply, input, output, halt = 99
};

enum class mode {
	position, immediate
};

std::vector<int> process(std::vector<int> program, int input) {
	size_t ip{ 0 };
	while (static_cast<opcode>(program.at(ip)) != opcode::halt) {
		mode param1_mode{ mode::position };
		mode param2_mode{ mode::position };
		mode param3_mode{ mode::position };
		if (program.at(ip) > 100) {
			int modes{ program.at(ip) / 100 };
			param1_mode = modes % 10 == 0 ? mode::position : mode::immediate;
			modes /= 10;
			param2_mode = modes % 10 == 0 ? mode::position : mode::immediate;
			modes /= 10;
			param3_mode = modes % 10 == 0 ? mode::position : mode::immediate;
		}

		opcode op{ program.at(ip) < 100 ? static_cast<opcode>(program.at(ip)) : static_cast<opcode>(program.at(ip) % 100) };

		switch (op) {
		case opcode::add:
		{
			auto param1{ param1_mode == mode::position ? program.at(program.at(ip + 1)) : program.at(ip + 1) };
			auto param2{ param2_mode == mode::position ? program.at(program.at(ip + 2)) : program.at(ip + 2) };
			auto param3{ param3_mode == mode::immediate ? program.at(program.at(ip + 3)) : program.at(ip + 3) }; // never in immediate mode for writes
			program.at(param3) = param1 + param2;
			ip += 4;
			break;
		}
		case opcode::multiply:
		{
			auto param1{ param1_mode == mode::position ? program.at(program.at(ip + 1)) : program.at(ip + 1) };
			auto param2{ param2_mode == mode::position ? program.at(program.at(ip + 2)) : program.at(ip + 2) };
			auto param3{ param3_mode == mode::immediate ? program.at(program.at(ip + 3)) : program.at(ip + 3) }; // never in immediate mode for writes
			program.at(param3) = param1 * param2;
			ip += 4;
			break;
		}
		case opcode::input:
		{
			auto param1{ program.at(ip + 1) };
			program.at(param1) = input;
			ip += 2;
			break;
		}
		case opcode::output:
		{
			auto param1{ param1_mode == mode::position ? program.at(program.at(ip + 1)) : program.at(ip + 1) };
			std::cout << "output: " << param1 << "\n";
			ip += 2;
			break;
		}
		default:
			throw std::logic_error("Bad opcode");
		}
	}
	return program;
}

int main() {
	std::vector<int> program{ 3,225,1,225,6,6,1100,1,238,225,104,0,1102,59,58,224,1001,224,-3422,
		224,4,224,102,8,223,223,101,3,224,224,1,224,223,223,1101,59,30,225,1101,53,84,224,
		101,-137,224,224,4,224,1002,223,8,223,101,3,224,224,1,223,224,223,1102,42,83,225,
		2,140,88,224,1001,224,-4891,224,4,224,1002,223,8,223,1001,224,5,224,1,223,224,223,
		1101,61,67,225,101,46,62,224,1001,224,-129,224,4,224,1002,223,8,223,101,5,224,224,
		1,223,224,223,1102,53,40,225,1001,35,35,224,1001,224,-94,224,4,224,102,8,223,223,101,
		6,224,224,1,223,224,223,1101,5,73,225,1002,191,52,224,1001,224,-1872,224,4,224,1002,
		223,8,223,1001,224,5,224,1,223,224,223,102,82,195,224,101,-738,224,224,4,224,1002,223,
		8,223,1001,224,2,224,1,224,223,223,1101,83,52,225,1101,36,77,225,1101,9,10,225,1,113,
		187,224,1001,224,-136,224,4,224,1002,223,8,223,101,2,224,224,1,224,223,223,4,223,99,
		0,0,0,677,0,0,0,0,0,0,0,0,0,0,0,1105,0,99999,1105,227,247,1105,1,99999,1005,227,
		99999,1005,0,256,1105,1,99999,1106,227,99999,1106,0,265,1105,1,99999,1006,0,99999,
		1006,227,274,1105,1,99999,1105,1,280,1105,1,99999,1,225,225,225,1101,294,0,0,105,1,
		0,1105,1,99999,1106,0,300,1105,1,99999,1,225,225,225,1101,314,0,0,106,0,0,1105,1,
		99999,1007,226,226,224,1002,223,2,223,1006,224,329,1001,223,1,223,1108,226,226,224,
		102,2,223,223,1006,224,344,101,1,223,223,1007,677,677,224,102,2,223,223,1006,224,
		359,101,1,223,223,1108,677,226,224,1002,223,2,223,1005,224,374,1001,223,1,223,7,
		677,226,224,102,2,223,223,1005,224,389,1001,223,1,223,1008,677,677,224,1002,223,
		2,223,1005,224,404,101,1,223,223,108,226,226,224,1002,223,2,223,1006,224,419,101,
		1,223,223,1008,226,677,224,1002,223,2,223,1006,224,434,1001,223,1,223,1107,677,
		226,224,1002,223,2,223,1005,224,449,101,1,223,223,1008,226,226,224,102,2,223,
		223,1005,224,464,1001,223,1,223,8,226,226,224,1002,223,2,223,1006,224,479,1001,
		223,1,223,107,226,677,224,102,2,223,223,1005,224,494,1001,223,1,223,7,226,226,
		224,102,2,223,223,1005,224,509,1001,223,1,223,107,226,226,224,102,2,223,223,
		1005,224,524,101,1,223,223,107,677,677,224,1002,223,2,223,1006,224,539,101,1,
		223,223,8,677,226,224,1002,223,2,223,1006,224,554,101,1,223,223,1107,677,677,
		224,1002,223,2,223,1005,224,569,101,1,223,223,108,226,677,224,1002,223,2,223,
		1006,224,584,101,1,223,223,7,226,677,224,1002,223,2,223,1005,224,599,1001,223,
		1,223,8,226,677,224,102,2,223,223,1006,224,614,1001,223,1,223,108,677,677,224,
		1002,223,2,223,1006,224,629,1001,223,1,223,1007,226,677,224,1002,223,2,223,1006,
		224,644,101,1,223,223,1108,226,677,224,102,2,223,223,1005,224,659,1001,223,1,223,
		1107,226,677,224,102,2,223,223,1006,224,674,1001,223,1,223,4,223,99,226 };

	// Part 1

	//auto output1{ process({1002}, 1) };
	//auto ex1{ process({3,0,4,0,99}, 1) };
	//auto ex2{ process({1002,4,3,4,33}, 1) };

	std::vector<int> output = process(program, 1);

	return 0;
}

