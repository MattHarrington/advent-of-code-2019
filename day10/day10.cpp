// https://adventofcode.com/2019/day/10

#include <algorithm>
#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
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

std::vector<int> reachable_asteroids(const std::vector<Point>& asteroids) {
	std::vector<int> reachable_asteroids;
	for (const auto& asteroid : asteroids) {
		int reachable{ 0 };
		for (const auto& next_asteroid : asteroids) {
			if (next_asteroid == asteroid) continue;
			int x_dist{ std::abs(asteroid.x - next_asteroid.y) };
			int y_dist{ std::abs(asteroid.y - next_asteroid.y) };
			if (y_dist != 0 && x_dist % y_dist == 0) {
				x_dist /= y_dist;
			}
			else if (x_dist != 0 && y_dist % x_dist == 0) {
				y_dist /= x_dist;
			}
			int x{ next_asteroid.x };
			int y{ next_asteroid.y };
			while (x_dist != asteroid.x && y_dist != asteroid.y) {
				if (x_dist > asteroid.x) {
					x -= x_dist;
				}
				else {
					x += x_dist;
				}
				if (y_dist > asteroid.y) {
					y -= y_dist;
				}
				else {
					y += y_dist;
				}
				if (std::find(begin(asteroids), end(asteroids), Point{ x,y }) != end(asteroids)) {
					goto NEXT_ASTEROID;
				}
			}
			reachable += 1;
		NEXT_ASTEROID:
			std::cout << "NEXT_ASTEROID" << "\n";
		}
		reachable_asteroids.push_back(reachable);
	}
	return reachable_asteroids;
}

int main()
{
	std::vector<std::vector<bool>> example1_asteroid_map{ read_input_file("day10_example1_input.txt") };
	std::vector<Point> example1_asteroids{ get_asteroids(example1_asteroid_map) };
	std::vector<int> example1_reachable_asteroids{ reachable_asteroids(example1_asteroids) };

	std::vector<std::vector<bool>> asteroid_map{ read_input_file("day10_input.txt") };
	assert(asteroid_map.size() == 26);

	std::vector<Point> asteroids{ get_asteroids(asteroid_map) };

	return 0;
}

