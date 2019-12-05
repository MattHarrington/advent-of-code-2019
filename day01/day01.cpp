// https://adventofcode.com/2019/day/1

#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

constexpr int get_fuel_required(int mass) noexcept {
	const int fuel_required{ (mass / 3) - 2 };
	return fuel_required <= 0 ? 0 : fuel_required;
}

int get_additional_fuel(int mass) {
	if (mass == 0) { return 0; }
	const int fuel_required{ get_fuel_required(mass) };
	return fuel_required + get_additional_fuel(fuel_required);
}

int main() {
	// Part 1

	// Tests
	assert(get_fuel_required(12) == 2);
	assert(get_fuel_required(14) == 2);
	assert(get_fuel_required(1969) == 654);
	assert(get_fuel_required(100756) == 33583);

	std::fstream in{ "day01_input.txt" };
	std::string mass;
	std::vector<int> module_masses;
	while (getline(in, mass)) {
		module_masses.push_back(std::stoi(mass));
	}

	std::vector<int> part_one_fuel_requirements(module_masses.size());
	std::transform(begin(module_masses), end(module_masses), begin(part_one_fuel_requirements), get_fuel_required);
	const int part_one_answer{ std::accumulate(begin(part_one_fuel_requirements), end(part_one_fuel_requirements), 0) };

	std::cout << "part_one_answer: " << part_one_answer << "\n";
	assert(part_one_answer == 3231195);

	// Part 2

	// Tests
	assert(get_additional_fuel(14) == 2);
	assert(get_additional_fuel(1969) == 966);
	assert(get_additional_fuel(100756) == 50346);

	std::vector<int> part_two_fuel_requirements(module_masses.size());

	std::transform(begin(module_masses), end(module_masses), begin(part_two_fuel_requirements), get_additional_fuel);
	const int part_two_answer{ std::accumulate(begin(part_two_fuel_requirements), end(part_two_fuel_requirements), 0) };

	std::cout << "part_two_answer: " << part_two_answer << "\n";
	assert(part_two_answer == 4843929);

	return 0;
}

