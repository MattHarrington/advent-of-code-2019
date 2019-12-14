// https://adventofcode.com/2019/day/5

#include <cassert>
#include <iostream>
#include <stdexcept>
#include <vector>

enum opcode {
	add = 1, multiply, input, output, halt = 99
};

std::vector<int> process(std::vector<int> input) {
	size_t pos{ 0 };
	while (input.at(pos) != halt) {
		auto input1_pos{ input.at(pos + 1) };
		auto input2_pos{ input.at(pos + 2) };
		auto output_pos{ input.at(pos + 3) };

		switch (input.at(pos)) {
		case add:
			input.at(output_pos) = input.at(input1_pos) + input.at(input2_pos);
			break;
		case multiply:
			input.at(output_pos) = input.at(input1_pos) * input.at(input2_pos);
			break;
		//case input:
		//	input.at(output_pos) = 
		default:
			throw std::logic_error("Bad opcode");
		}
		pos += 4;
	}
	return input;
}

int main() {
	std::vector<int> ex1{ 1,9,10,3,2,3,11,0,99,30,40,50 };
	std::vector<int> ex1_answer{ 3500, 9, 10, 70, 2, 3, 11, 0, 99, 30, 40, 50 };
	assert(process(ex1) == ex1_answer);

	std::vector<int> ex2{ 1,0,0,0,99 };
	std::vector<int> ex2_answer{ 2,0,0,0,99 };
	assert(process(ex2) == ex2_answer);

	std::vector<int> ex3{ 2,3,0,3,99 };
	std::vector<int> ex3_answer{ 2,3,0,6,99 };
	assert(process(ex3) == ex3_answer);

	std::vector<int> ex4{ 2,4,4,5,99,0 };
	std::vector<int> ex4_answer{ 2,4,4,5,99,9801 };
	assert(process(ex4) == ex4_answer);

	std::vector<int> ex5{ 1,1,1,4,99,5,6,0,99 };
	std::vector<int> ex5_answer{ 30,1,1,4,2,5,6,0,99 };
	assert(process(ex5) == ex5_answer);

	std::vector<int> input{ 3,225,1,225,6,6,1100,1,238,225,104,0,1102,59,58,224,1001,224,-3422,
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

	// Change input per the problem statement:
	input.at(1) = 12;
	input.at(2) = 2;

	std::vector<int> output1 = process(input);
	const int part_one_answer = output1.at(0);
	std::cout << "part_one_answer: " << part_one_answer << "\n";
	assert(part_one_answer == 5534943);

	// Part 2

	int part_two_answer{ -1 };

	for (int n{ 0 }; n < 100; ++n) {
		input.at(1) = n;
		for (int v{ 0 }; v < 100; ++v) {
			input.at(2) = v;
			std::vector<int> output2 = process(input);
			if (output2.at(0) == 19690720) {
				part_two_answer = 100 * n + v;
				// Set n, v to break out of loops:
				n = 5000;
				v = 5000;
			}
		}
	}
	std::cout << "part_two_answer: " << part_two_answer << "\n";
	assert(part_two_answer == 7603);

	return 0;
}