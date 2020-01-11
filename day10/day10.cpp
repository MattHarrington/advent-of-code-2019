// https://adventofcode.com/2019/day/10

#include <algorithm>
#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <numeric>
#include <stdexcept>
#include <string>
#include <vector>

std::vector<std::vector<bool>> read_input_file(const std::string& filename) {
	std::vector<std::vector<bool>> asteroid_map;
	std::fstream in{ filename };
	if (!in) throw std::runtime_error("File not found");
	std::string line;
	while (getline(in, line)) {
		std::vector<bool> row;
		for (const char point : line) {
			if (point == '#') row.push_back(true);
			else row.push_back(false);
		}
		asteroid_map.push_back(row);
	}
	return asteroid_map;
}

struct Point {
	int x;
	int y;
};

bool operator==(const Point& lhs, const Point& rhs) noexcept
{
	return lhs.x == rhs.x && lhs.y == rhs.y;
}

std::vector<Point> get_asteroids(const std::vector<std::vector<bool>>& asteroid_map) {
	std::vector<Point> asteroids;
	const int height{ static_cast<int>(asteroid_map.size()) };
	const int width{ static_cast<int>(asteroid_map.front().size()) };
	for (int y{ 0 }; y < height; ++y) {
		for (int x{ 0 }; x < width; ++x) {
			if (asteroid_map.at(y).at(x)) {
				asteroids.emplace_back(Point{ x, y });
			}
		}
	}
	return asteroids;
}

std::vector<int> num_reachable_asteroids(const std::vector<Point>& asteroids) {
	std::vector<int> nums_reachable_asteroids;
	for (const auto& asteroid : asteroids) {
		int reachable{ 0 };
		for (const auto& next_asteroid : asteroids) {
			if (next_asteroid == asteroid) continue;
			int x_dist{ std::abs(asteroid.x - next_asteroid.x) };
			int y_dist{ std::abs(asteroid.y - next_asteroid.y) };
			if (x_dist == 0) {
				y_dist = 1;
			}
			else if (y_dist == 0) {
				x_dist = 1;
			}
			else { 
				int gcd{std::gcd(x_dist, y_dist)};
				x_dist /= gcd;
				y_dist /= gcd;
			}
			int x{ next_asteroid.x };
			int y{ next_asteroid.y };
			bool looping{ true };
			while (looping) {
				if (x_dist == 0) {

				}
				else if (next_asteroid.x > asteroid.x) {
					x -= x_dist;
				}
				else if (next_asteroid.x < asteroid.x) {
					x += x_dist;
				}
				if (y_dist == 0) {

				}
				else if (next_asteroid.y > asteroid.y) {
					y -= y_dist;
				}
				else if (next_asteroid.y < asteroid.y) {
					y += y_dist;
				}
				if (x == asteroid.x && y == asteroid.y) {
					++reachable;
					looping = false;
				}
				else if (std::find(begin(asteroids), end(asteroids), Point{ x,y }) != end(asteroids)) {
					looping = false;
				}
			}
		}
		nums_reachable_asteroids.push_back(reachable);
	}
	return nums_reachable_asteroids;
}

int main()
{
	std::vector<std::vector<bool>> example1_asteroid_map{ read_input_file("day10_example1_input.txt") };
	std::vector<Point> example1_asteroids{ get_asteroids(example1_asteroid_map) };
	std::vector<int> example1_reachable_asteroids{ num_reachable_asteroids(example1_asteroids) };
	const int part1_example1_answer{ *std::max_element(begin(example1_reachable_asteroids), end(example1_reachable_asteroids)) };
	std::cout << "part1_example1_answer: " << part1_example1_answer << "\n";
	assert(part1_example1_answer == 8);

	std::vector<std::vector<bool>> example2_asteroid_map{ read_input_file("day10_example2_input.txt") };
	std::vector<Point> example2_asteroids{ get_asteroids(example2_asteroid_map) };
	std::vector<int> example2_reachable_asteroids{ num_reachable_asteroids(example2_asteroids) };
	const int part1_example2_answer{ *std::max_element(begin(example2_reachable_asteroids), end(example2_reachable_asteroids)) };
	std::cout << "part1_example2_answer: " << part1_example2_answer << "\n";
	assert(part1_example2_answer == 33);

	std::vector<std::vector<bool>> example3_asteroid_map{ read_input_file("day10_example3_input.txt") };
	std::vector<Point> example3_asteroids{ get_asteroids(example3_asteroid_map) };
	std::vector<int> example3_reachable_asteroids{ num_reachable_asteroids(example3_asteroids) };
	const int part1_example3_answer{ *std::max_element(begin(example3_reachable_asteroids), end(example3_reachable_asteroids)) };
	std::cout << "part1_example3_answer: " << part1_example3_answer << "\n";
	assert(part1_example3_answer == 35);

	std::vector<std::vector<bool>> example4_asteroid_map{ read_input_file("day10_example4_input.txt") };
	std::vector<Point> example4_asteroids{ get_asteroids(example4_asteroid_map) };
	std::vector<int> example4_reachable_asteroids{ num_reachable_asteroids(example4_asteroids) };
	const int part1_example4_answer{ *std::max_element(begin(example4_reachable_asteroids), end(example4_reachable_asteroids)) };
	std::cout << "part1_example4_answer: " << part1_example4_answer << "\n";
	assert(part1_example4_answer == 41);

	std::vector<std::vector<bool>> example5_asteroid_map{ read_input_file("day10_example5_input.txt") };
	std::vector<Point> example5_asteroids{ get_asteroids(example5_asteroid_map) };
	std::vector<int> example5_reachable_asteroids{ num_reachable_asteroids(example5_asteroids) };
	const int example5_part1_answer{ *std::max_element(begin(example5_reachable_asteroids), end(example5_reachable_asteroids)) };
	std::cout << "part1_example5_answer: " << example5_part1_answer << "\n";
	assert(example5_part1_answer == 210);

	std::vector<std::vector<bool>> asteroid_map{ read_input_file("day10_input.txt") };
	std::vector<Point> asteroids{ get_asteroids(asteroid_map) };
	std::vector<int> reachable_asteroids{ num_reachable_asteroids(asteroids) };
	const int part1_answer{ *std::max_element(begin(reachable_asteroids), end(reachable_asteroids)) };
	std::cout << "part1_answer: " << part1_answer << "\n";
	assert(part1_answer == 274);

	return 0;
}

