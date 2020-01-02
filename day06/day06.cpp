// https://adventofcode.com/2019/day/6

#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <regex>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>
#include "Tree.hpp"

/// <summary>Parse the input file into a vector of strings</summary>
std::vector<std::string> get_input(const std::string& input_filename) {
	std::fstream in{ input_filename };
	if (!in) throw std::runtime_error{ "Cannot open file" };
	std::vector<std::string> data;
	std::string line;
	while (getline(in, line)) {
		data.push_back(line);
	}
	return data;
}

using adj_list_t = std::unordered_map<std::string, std::vector<std::string>>;
/// <summary>Create an adjacency list from the input data</summary>
adj_list_t get_adj_list(const std::vector<std::string>& data) {
	std::unordered_map<std::string, std::vector<std::string>> adj_list;
	const std::regex rx{ R"(([A-Z\d]+)\)([A-Z\d]+))" };
	for (const auto& item : data) {
		std::smatch sm;
		std::regex_match(item, sm, rx);
		adj_list[sm[1]].push_back(sm[2]);
	}
	return adj_list;
}

using rev_adj_list_t = std::unordered_map<std::string,std::string>;
/// <summary>Create an adjacency list for the reverse paths from the input data</summary>
rev_adj_list_t get_rev_adj_list(const std::vector<std::string>& data) {
	rev_adj_list_t rev_adj_list;
	const std::regex rx{ R"(([A-Z\d]+)\)([A-Z\d]+))" };
	for (const auto& item : data) {
		std::smatch sm;
		std::regex_match(item, sm, rx);
		rev_adj_list[sm[2]] = sm[1];
	}
	return rev_adj_list;
}

/// <summary>Get the reverse path from an orbiter to the Center of Mass</summary>
std::vector<std::string> get_reverse_path(rev_adj_list_t rev_adj_list, std::string orbiter) {
	std::vector<std::string> path;
	while (orbiter != "COM") {
		orbiter = rev_adj_list[orbiter];
		path.push_back(orbiter);
	}
	return path;
}

/// <summary>Determine reverse paths to Center of Mass from YOU and SAN.
/// Path from YOU to SAN is union of the unique elements in each path.</summary>
size_t part_two(std::vector<std::string> data) {
	rev_adj_list_t rev_adj_list{ get_rev_adj_list(data) };
	auto path_from_you{ get_reverse_path(rev_adj_list, "YOU") };
	auto path_from_san{ get_reverse_path(rev_adj_list, "SAN") };

	// std::set_difference requires input to be sorted
	std::sort(begin(path_from_you), end(path_from_you));
	std::sort(begin(path_from_san), end(path_from_san));

	std::vector<std::string> unique_elements;
	// Elements in path_from_you not in path_from_san:
	std::set_difference(begin(path_from_you), end(path_from_you),
		begin(path_from_san), end(path_from_san), std::back_inserter(unique_elements));
	// Elements in path_from_san not in path_from_you:
	std::set_difference(begin(path_from_san), end(path_from_san),
		begin(path_from_you), end(path_from_you), std::back_inserter(unique_elements));
	return unique_elements.size();
}

int main() {
	std::string input_filename{ "day06_input.txt" };

	std::vector<std::string> problem_data{ get_input(input_filename) };
	std::vector<std::string> part_one_sample_data{ {"COM)B"}, {"B)C"}, {"C)D"}, {"D)E"}, {"E)F"}, {"B)G"},
		{"G)H"}, {"D)I"}, {"E)J"}, {"J)K"}, {"K)L"} };
	std::vector<std::string> part_two_sample_data{ {"COM)B"}, {"B)C"}, {"C)D"}, {"D)E"}, {"E)F"}, {"B)G"},
		{"G)H"}, {"D)I"}, {"E)J"}, {"J)K"}, {"K)L"}, {"K)YOU"}, {"I)SAN"} };

	adj_list_t part_one_sample_adj_list{ get_adj_list(part_one_sample_data) };
	adj_list_t adj_list{ get_adj_list(problem_data) };
	
	// Part 1 sample
	Tree<std::string> sample_tree(part_one_sample_adj_list, "COM");
	const int sample_part_one_answer{ sample_tree.get_num_orbits() };
	assert(sample_part_one_answer == 42);

	// Part 1 problem data
	Tree<std::string> tree(adj_list, "COM");
	const int part_one_answer{ tree.get_num_orbits() };
	std::cout << "part_one_answer: " << part_one_answer << "\n";
	assert(part_one_answer == 315757);
	
	// Part 2 sample
	const size_t sample_part_two_answer{ part_two(part_two_sample_data) };
	assert(sample_part_two_answer == 4);

	// Part 2 problem data
	const size_t part_two_answer{ part_two(problem_data) };
	std::cout << "part_two_answer: " << part_two_answer << "\n";
	assert(part_two_answer == 481);

	return 0;
}

