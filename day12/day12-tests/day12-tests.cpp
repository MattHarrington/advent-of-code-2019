// https://adventofcode.com/2019/day/12

#include <catch.hpp>
#include <numeric>
#include "day12-lib.h"

TEST_CASE("sample after 1 timestep should be correct", "[part_one]") {
    const std::vector<Moon> sample_moons{
        Moon{{-1,0,2}, {0,0,0}},
        Moon{{2,-10,-7}, {0,0,0}},
        Moon{{4,-8,8}, {0,0,0}},
        Moon{{3,5,-1}, {0,0,0}}
    };
    const std::vector<Moon> moons_after_one_timestep{
        Moon{{2,-1,1}, {3,-1,-1}},
        Moon{{3,-7,-4}, {1,3,3}},
        Moon{{1,-7,5}, {-3,1,-3}},
        Moon{{2,2,0}, {-1,-3,1}}
    };
    REQUIRE(timestep(sample_moons) == moons_after_one_timestep);
}

TEST_CASE("sample after 10 timesteps should be correct", "[part_one]") {
    std::vector<Moon> sample_moons{
        Moon{{-1,0,2}, {0,0,0}},
        Moon{{2,-10,-7}, {0,0,0}},
        Moon{{4,-8,8}, {0,0,0}},
        Moon{{3,5,-1}, {0,0,0}}
    };
    const std::vector<Moon> moons_after_10_timesteps{
        Moon{{2,1,-3}, {-3,-2,1}},
        Moon{{1,-8,0}, {-1,1,3}},
        Moon{{3,-6,1}, {3,2,-3}},
        Moon{{2,0,4}, {1,-1,-1}}
    };
    for (int i{ 0 }; i < 10; ++i) {
        sample_moons = timestep(sample_moons);
    }
    REQUIRE(sample_moons == moons_after_10_timesteps);
}

TEST_CASE("energy of sample moon 1 should be 36", "[part_one]") {
    const Moon moon{ {2,1,-3}, {-3,-2,1} };
    REQUIRE(get_total_energy(moon) == 36);
}

TEST_CASE("energy of sample moon 2 should be 45", "[part_one]") {
    const Moon moon{ {1,-8,0}, {-1,1,3} };
    REQUIRE(get_total_energy(moon) == 45);
}

TEST_CASE("energy after 10 timesteps should be 179", "[part_one]") {
    const std::vector<Moon> moons_after_10_timesteps{
        Moon{{2,1,-3}, {-3,-2,1}},
        Moon{{1,-8,0}, {-1,1,3}},
        Moon{{3,-6,1}, {3,2,-3}},
        Moon{{2,0,4}, {1,-1,-1}}
    };
    const int total_energy{ std::accumulate(begin(moons_after_10_timesteps), end(moons_after_10_timesteps),
        0, [](int t, Moon m) noexcept {return t + get_total_energy(m); }) };
    REQUIRE(total_energy == 179);
}

TEST_CASE("sample moons should repeat x value at timestep 18", "[part_two]") {
    std::vector<Moon> sample_moons{
        Moon{{-1,0,2}, {0,0,0}},
        Moon{{2,-10,-7}, {0,0,0}},
        Moon{{4,-8,8}, {0,0,0}},
        Moon{{3,5,-1}, {0,0,0}}
    };
    int step{ 0 };
    do {
        sample_moons = timestep(sample_moons);
        ++step;
    } while (sample_moons.at(0).position.x != -1 || sample_moons.at(1).position.x != 2
        || sample_moons.at(2).position.x != 4 || sample_moons.at(3).position.x != 3
        || sample_moons.at(0).velocity.x_velocity == sample_moons.at(1).velocity.x_velocity ==
        sample_moons.at(2).velocity.x_velocity == sample_moons.at(3).velocity.x_velocity == 0);

    REQUIRE(step == 18);
}

TEST_CASE("sample moons should repeat y value at timestep 28", "[part_two]") {
    std::vector<Moon> sample_moons{
        Moon{{-1,0,2}, {0,0,0}},
        Moon{{2,-10,-7}, {0,0,0}},
        Moon{{4,-8,8}, {0,0,0}},
        Moon{{3,5,-1}, {0,0,0}}
    };
    int step{ 0 };
    do {
        sample_moons = timestep(sample_moons);
        ++step;
    } while (sample_moons.at(0).position.y != 0 || sample_moons.at(1).position.y != -10 ||
        sample_moons.at(2).position.y != -8 || sample_moons.at(3).position.y != 5
        || sample_moons.at(0).velocity.y_velocity == sample_moons.at(1).velocity.y_velocity ==
        sample_moons.at(2).velocity.y_velocity == sample_moons.at(3).velocity.y_velocity == 0);

    REQUIRE(step == 28);
}

TEST_CASE("sample moons should repeat z value at timestep 44", "[part_two]") {
    std::vector<Moon> sample_moons{
        Moon{{-1,0,2}, {0,0,0}},
        Moon{{2,-10,-7}, {0,0,0}},
        Moon{{4,-8,8}, {0,0,0}},
        Moon{{3,5,-1}, {0,0,0}}
    };
    int step{ 0 };
    do {
        sample_moons = timestep(sample_moons);
        ++step;
    } while (sample_moons.at(0).position.z != 2 || sample_moons.at(1).position.z != -7 ||
        sample_moons.at(2).position.z != 8 || sample_moons.at(3).position.z != -1
        || sample_moons.at(0).velocity.z_velocity == sample_moons.at(1).velocity.z_velocity ==
        sample_moons.at(2).velocity.z_velocity == sample_moons.at(3).velocity.z_velocity == 0);

    REQUIRE(step == 44);
}

TEST_CASE("sample moons should repeat state at timestep 2722", "[part_two]") {
    // 18, 28, and 44 are results from other TEST_CASEs
    constexpr int repeat_timestep_x_y{ std::lcm(18,28) };
    constexpr int repeat_timestep_xy_z{ std::lcm(repeat_timestep_x_y, 44) };
    REQUIRE(repeat_timestep_xy_z == 2772);
}

