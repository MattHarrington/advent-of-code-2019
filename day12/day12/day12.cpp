// https://adventofcode.com/2019/day/12

#include <gsl/gsl_assert>
#include <iostream>
#include <numeric>
#include "day12-lib.h"

int main() {
    const std::vector<Moon> moons{
        Moon{ {12,0,-15},  {0,0,0} },
        Moon{ {-8,-5,-10}, {0,0,0} },
        Moon{ {7,-17,1},   {0,0,0} },
        Moon{ {2,-11,-6},  {0,0,0} }
    };

    // Sample:
    //const std::vector<Moon> moons{
    //    Moon{{-1,0,2},    {0,0,0}},
    //    Moon{{2,-10,-7},  {0,0,0}},
    //    Moon{{4,-8,8},    {0,0,0}},
    //    Moon{{3,5,-1},    {0,0,0}}
    //};

    // Sample:
    //const std::vector<Moon> moons{
    //    Moon{ {-8,-10,0}, {0,0,0} },
    //    Moon{ {5,5,10},   {0,0,0} },
    //    Moon{ {2,-7,3},   {0,0,0} },
    //    Moon{ {9,-8,-3},  {0,0,0} }
    //};

    // Part 1

    std::vector<Moon> part1_moons{ moons };
    for (int i{ 0 }; i < 1000; ++i) {
        part1_moons = timestep(part1_moons);
    }

    const int part1_answer{ std::accumulate(begin(part1_moons), end(part1_moons), 0,
        [](int t, Moon m) noexcept {return t + get_total_energy(m); }) };
    std::cout << "part1_answer: " << part1_answer << "\n";
    Ensures(part1_answer == 7636);

    // Part 2

    std::vector<Moon> part2_moons{ moons };
    long long x_step{ 0 };
    do {
        part2_moons = timestep(part2_moons);
        ++x_step;
    } while (part2_moons.at(0).position.x != moons.at(0).position.x || part2_moons.at(1).position.x != moons.at(1).position.x
        || part2_moons.at(2).position.x != moons.at(2).position.x || part2_moons.at(3).position.x != moons.at(3).position.x
        || part2_moons.at(0).velocity.x_velocity == part2_moons.at(1).velocity.x_velocity ==
        part2_moons.at(2).velocity.x_velocity == part2_moons.at(3).velocity.x_velocity == 0);

    part2_moons = moons;
    long long y_step{ 0 };
    do {
        part2_moons = timestep(part2_moons);
        ++y_step;
    } while (part2_moons.at(0).position.y != moons.at(0).position.y || part2_moons.at(1).position.y != moons.at(1).position.y ||
        part2_moons.at(2).position.y != moons.at(2).position.y || part2_moons.at(3).position.y != moons.at(3).position.y
        || part2_moons.at(0).velocity.y_velocity == part2_moons.at(1).velocity.y_velocity ==
        part2_moons.at(2).velocity.y_velocity == part2_moons.at(3).velocity.y_velocity == 0);

    part2_moons = moons;
    long long z_step{ 0 };
    do {
        part2_moons = timestep(part2_moons);
        ++z_step;
    } while (part2_moons.at(0).position.z != moons.at(0).position.z || part2_moons.at(1).position.z != moons.at(1).position.z ||
        part2_moons.at(2).position.z != moons.at(2).position.z || part2_moons.at(3).position.z != moons.at(3).position.z
        || part2_moons.at(0).velocity.z_velocity == part2_moons.at(1).velocity.z_velocity ==
        part2_moons.at(2).velocity.z_velocity == part2_moons.at(3).velocity.z_velocity == 0);

    const long long repeat_timestep_x_y{ std::lcm(x_step,y_step) };
    const long long part2_answer{ std::lcm(repeat_timestep_x_y, z_step) };
    std::cout << "part2_answer: " << part2_answer << "\n";
    Ensures(part2_answer == 281691380235984);
}

