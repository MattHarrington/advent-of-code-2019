// https://adventofcode.com/2019/day/4

#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <string>

// Alternative: use std::is_sorted()
bool digits_are_increasing(int i) noexcept {
	const int first_digit{ i / 100'000 };
	i %= 100'000;
	const int second_digit{ i / 10'000 };
	i %= 10'000;
	const int third_digit{ i / 1'000 };
	i %= 1'000;
	const int fourth_digit{ i / 100 };
	i %= 100;
	const int fifth_digit{ i / 10 };
	i %= 10;
	const int sixth_digit{ i };
	return (first_digit <= second_digit) && (second_digit <= third_digit)
		&& (third_digit <= fourth_digit) && (fourth_digit <= fifth_digit) && (fifth_digit <= sixth_digit);
}

bool part1_has_pair(int i) {
	std::string s{ std::to_string(i) };
	auto it{ std::adjacent_find(begin(s), end(s)) };
	return it != end(s);
}

// Alternative: count repeated digits & look for number of repeats == 2
bool part2_has_pair(int i) {
	std::string s{ std::to_string(i) };
	// Check from beginning up to the last 2 positions
	for (auto it{ begin(s) }; it < end(s) - 2; ++it) {
		if (*it == *(std::next(it)) && (*it != *(it + 2))) return true;
		while (it < end(s) - 1 && *it == *(std::next(it))){
			++it;
		}
	}
	// Check last 2 positions
	if (*(end(s) - 2) == *(end(s) - 1) && *(end(s) - 3) != *(end(s) - 2)) return true;
	return false;
}

int main()
{
	assert(digits_are_increasing(111'111) && part1_has_pair(111'111));
	assert(digits_are_increasing(223'450) == false);
	assert(part1_has_pair(223'450));
	assert(digits_are_increasing(123'789));
	assert(part1_has_pair(123'789) == false);

	int part_one_answer{ 0 };
	int part_two_answer{ 0 };

	for (int i = 206'938; i <= 679'128; i++)
	{
		if (digits_are_increasing(i) && part1_has_pair(i))
		{
			++part_one_answer;
		}
		if (digits_are_increasing(i) && part2_has_pair(i)) {
			++part_two_answer;
		}
	}
	std::cout << "part_one_answer: " << part_one_answer << "\n";
	assert(part_one_answer == 1653);

	assert(part2_has_pair(112'233));
	assert(part2_has_pair(123'444) == false);
	assert(part2_has_pair(111'122));

	std::cout << "part_two_answer: " << part_two_answer << "\n";
	assert(part_two_answer == 1133);
}

