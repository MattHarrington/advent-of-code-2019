// https://adventofcode.com/2019/day/2

#include <cassert>
#include <iostream>
#include <stdexcept>
#include <vector>

enum opcode {
	add = 1, multiply, halt = 99
};

std::vector<int> process(std::vector<int> input) {
	size_t pos{ 0 };
	while (input[pos] != halt) {
		auto input1_pos{ input[pos + 1] };
		auto input2_pos{ input[pos + 2] };
		auto output_pos{ input[pos + 3] };

		switch (input[pos]) {
		case add:
			input[output_pos] = input[input1_pos] + input[input2_pos];
			break;
		case multiply:
			input[output_pos] = input[input1_pos] * input[input2_pos];
			break;
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

	std::vector<int> input{ 1,0,0,3,1,1,2,3,1,3,4,3,1,5,0,3,2,6,1,19,1,19,9,23,1,23,9,27,1,10,27,
		31,1,13,31,35,1,35,10,39,2,39,9,43,1,43,13,47,1,5,47,51,1,6,51,55,1,13,55,59,1,59,6,63,1,
		63,10,67,2,67,6,71,1,71,5,75,2,75,10,79,1,79,6,83,1,83,5,87,1,87,6,91,1,91,13,95,1,95,6,
		99,2,99,10,103,1,103,6,107,2,6,107,111,1,13,111,115,2,115,10,119,1,119,5,123,2,10,123,127,
		2,127,9,131,1,5,131,135,2,10,135,139,2,139,9,143,1,143,2,147,1,5,147,0,99,2,0,14,0 };

	// Part 1

	// Change input per the problem statement:
	input[1] = 12;
	input[2] = 2;

	std::vector<int> output = process(input);
	int part_one_answer = output[0];
	std::cout << "part_one_answer: " << part_one_answer << "\n";
	assert(part_one_answer == 5534943);

	// Part 2

	int part_two_answer{ -1 };

	for (int n{ 0 }; n < 100; ++n) {
		input[1] = n;
		for (int v{ 0 }; v < 100; ++v) {
			input[2] = v;
			std::vector<int> output = process(input);
			if (output[0] == 19690720) {
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
