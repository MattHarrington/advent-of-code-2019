// https://adventofcode.com/2019/day/10

#define _USE_MATH_DEFINES

#include <algorithm>
#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <numeric>
#include <queue>
#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>

std::vector<std::vector<bool>> read_input_file(const std::string& filename) {
    std::vector<std::vector<bool>> asteroid_map;
    std::fstream in{ filename };
    if (!in) throw std::runtime_error("File not found");
    std::string line;
    while (getline(in, line)) {
        std::vector<bool> row;
        for (auto it{ begin(line) }; it != end(line); ++it) {
            if (*it == '#') row.push_back(true);
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

std::ostream& operator<< (std::ostream& os, const Point& p) {
    return (os << "{" << p.x << "," << p.y << "}");
}

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
            // Compute x & y distances to check if an asteroid blocks the path
            // between two asteroids. Uses GCD.
            int x_dist{ std::abs(asteroid.x - next_asteroid.x) };
            int y_dist{ std::abs(asteroid.y - next_asteroid.y) };
            if (x_dist == 0) {
                y_dist = 1;
            }
            else if (y_dist == 0) {
                x_dist = 1;
            }
            else {
                const int gcd{ std::gcd(x_dist, y_dist) };
                x_dist /= gcd;
                y_dist /= gcd;
            }
            int x{ next_asteroid.x };
            int y{ next_asteroid.y };
            bool looping{ true };
            while (looping) {
                // Check path to see if it's blocked by another asteroid
                if (next_asteroid.x > asteroid.x) {
                    x -= x_dist;
                }
                else if (next_asteroid.x < asteroid.x) {
                    x += x_dist;
                }

                if (next_asteroid.y > asteroid.y) {
                    y -= y_dist;
                }
                else if (next_asteroid.y < asteroid.y) {
                    y += y_dist;
                }

                if (x == asteroid.x && y == asteroid.y) {
                    // Reached target asteroid without being blocked
                    ++reachable;
                    looping = false;
                }
                else if (std::find(begin(asteroids), end(asteroids), Point{ x,y }) != end(asteroids)) {
                    // Found asteroid at x,y in list of asteroids, and it's not the target.
                    // Therefore, astertoid at x,y must be blocking path from source to target.
                    looping = false;
                }
            }
        }
        nums_reachable_asteroids.push_back(reachable);
    }
    return nums_reachable_asteroids;
}

int manhattan_distance(const Point& a, const Point& b) noexcept {
    return (std::abs(a.x - b.x) + std::abs(a.y - b.y));
}

int part_two(const Point& listening_station, std::vector<Point>& asteroids) {
    // Put angles into a vector, so they're sortable.
    std::vector < std::tuple< double, Point, int >> angles; // Angle, asteroid coordinates, distance to listening_station
    for (const auto& asteroid : asteroids) {
        if (asteroid == listening_station) continue;
        double angle{ std::atan2(asteroid.x - listening_station.x, asteroid.y - listening_station.y) };
        angle *= 180 / M_PI; // Convert to degrees, for convenience
        angle = std::abs(angle - 180); // Adjust because atan2 does not assume 0 degrees points north
        angles.emplace_back(std::make_tuple(angle, asteroid, manhattan_distance(asteroid, listening_station)));
    }
    // Sort by angle.  If angles are equal, also sort by distance to listening station.
    std::sort(begin(angles), end(angles), [](auto a, auto b) {
        if (std::get<0>(a) == std::get<0>(b)) return std::get<2>(a) < std::get<2>(b);
        else return std::get<0>(a) < std::get<0>(b); }
    );

    // Create a queue from the vector, because pop() makes it easier to find 200th asteroid.
    // Note: this fails if laser has to sweep through 360 degrees before finding 200th asteroid.
    std::queue<std::tuple<double, Point, int>> q;
    for (const auto& elem : angles) q.push(elem);

    // Find 200th destroyed asteroid
    int count{ 0 };
    auto asteroid{ q.front() };
    while (count < 200) {
        asteroid = q.front();
        q.pop();
        // Fast forward past asteroids with same angle but farther away, because laser only destroys first one.
        // Warning: bad strategy if 200th asteroid is after one full laser rotation.
        while (std::get<0>(asteroid) == std::get<0>(q.front())) q.pop();
        ++count;
    }

    return 100 * std::get<1>(asteroid).x + std::get<1>(asteroid).y; // (100 * x) + y, per problem statement
}

int main() {

    // Part 1

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

    // Part 2

    const auto example5_listening_station_it{ std::max_element(begin(example5_reachable_asteroids), end(example5_reachable_asteroids)) };
    const auto example5_listening_station_idx{ std::distance(begin(example5_reachable_asteroids), example5_listening_station_it) };
    const Point example5_listening_station{ example5_asteroids.at(example5_listening_station_idx) };
    const int part2_example5_answer{ part_two(example5_listening_station, example5_asteroids) };
    std::cout << "part2_example5_answer: " << part2_example5_answer << "\n";
    assert(part2_example5_answer == 802);

    const auto listening_station_it{ std::max_element(begin(reachable_asteroids), end(reachable_asteroids)) };
    const auto listening_station_idx{ std::distance(begin(reachable_asteroids), listening_station_it) };
    const Point listening_station{ asteroids.at(listening_station_idx) };
    const int part2_answer{ part_two(listening_station, asteroids) };
    std::cout << "part2_answer: " << part2_answer << "\n";
    assert(part2_answer == 305);

    return 0;
}

