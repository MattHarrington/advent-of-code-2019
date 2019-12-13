// https://adventofcode.com/2019/day/4

#include <cassert>
#include <iostream>
#include <iterator>
#include <string>

bool digits_are_increasing(int i) {
	int first_digit{ i / 100'000 };
	i %= 100'000;
	int second_digit{ i / 10'000 };
	i %= 10'000;
	int third_digit{ i / 1'000 };
	i %= 1'000;
	int fourth_digit{ i / 100 };
	i %= 100;
	int fifth_digit{ i / 10 };
	i %= 10;
	int sixth_digit{ i };
	return (first_digit <= second_digit) && (second_digit <= third_digit)
		&& (third_digit <= fourth_digit) && (fourth_digit <= fifth_digit) && (fifth_digit <= sixth_digit);
}

bool has_repeated_digit(int i) {
	std::string s{ std::to_string(i) };
	for (auto it{ begin(s) }; it < std::prev(end(s)); ++it) {
		if (*it == *(std::next(it))) return true;
	}
	return false;
}

//123'444
bool part2_repeated_digit(int i) {
	std::string s{ std::to_string(i) };
	for (auto it{ begin(s) }; it < end(s) - 2; ++it) {
		if (*it == *(std::next(it)) && *it == *(it + 2)) it += 2;
		else if (*it == *(std::next(it)) && (*it != *(it + 2))) return true;
	}
	if (*(end(s) - 2) == *(end(s) - 1) && *(end(s) - 3) != *(end(s) - 2)) return true;
	return false;
}

int main()
{
	assert(digits_are_increasing(111'111) && has_repeated_digit(111'111));
	assert(digits_are_increasing(223'450) == false);
	assert(has_repeated_digit(223'450));
	assert(digits_are_increasing(123'789));
	assert(has_repeated_digit(123'789) == false);

	int part_one_answer{ 0 };
	int part_two_answer{ 0 };

	for (int i = 206'938; i <= 679'128; i++)
	{
		if (digits_are_increasing(i) && has_repeated_digit(i))
		{
			++part_one_answer;
		}
		if (digits_are_increasing(i) && part2_repeated_digit(i)) {
			++part_two_answer;
		}
	}
	std::cout << "part_one_answer: " << part_one_answer << "\n";
	assert(part_one_answer == 1653);

	assert(part2_repeated_digit(112'233));
	assert(part2_repeated_digit(123'444) == false);
	assert(part2_repeated_digit(111'122));

	std::cout << "part_two_answer: " << part_two_answer << "\n";
}
// 1446 too high
// 478 too low
// 538 too low
// 1158 no
