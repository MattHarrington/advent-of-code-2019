// https://adventofcode.com/2019/day/12

#include <cmath>
#include "day12-lib.hpp"

bool operator==(const Moon lhs, const Moon rhs) noexcept {
    return lhs.position == rhs.position && lhs.velocity == rhs.velocity;
}

bool operator==(const Position lhs, const Position rhs) noexcept {
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}

bool operator==(const Velocity lhs, const Velocity rhs) noexcept {
    return lhs.x_velocity == rhs.x_velocity && lhs.y_velocity == rhs.y_velocity
        && lhs.z_velocity == rhs.z_velocity;
}

std::vector<Moon> timestep(const std::vector<Moon>& moons) {
    std::vector<Moon> new_moons{ moons };

    for (auto& moon : new_moons) {
        int x_adj{ 0 };
        int y_adj{ 0 };
        int z_adj{ 0 };
        for (const auto& other_moon : moons) {
            if (moon == other_moon) continue;
            if (moon.position.x > other_moon.position.x) --x_adj;
            else if (moon.position.x < other_moon.position.x) ++x_adj;
            if (moon.position.y > other_moon.position.y) --y_adj;
            else if (moon.position.y < other_moon.position.y) ++y_adj;
            if (moon.position.z > other_moon.position.z) --z_adj;
            else if (moon.position.z < other_moon.position.z) ++z_adj;
        }
        moon.velocity.x_velocity += x_adj;
        moon.velocity.y_velocity += y_adj;
        moon.velocity.z_velocity += z_adj;
        moon.position.x += moon.velocity.x_velocity;
        moon.position.y += moon.velocity.y_velocity;
        moon.position.z += moon.velocity.z_velocity;
    }

    return new_moons;
}

int get_potential_energy(const Moon& moon) noexcept {
    return std::abs(moon.position.x) + std::abs(moon.position.y) + std::abs(moon.position.z);
}

int get_kinetic_energy(const Moon& moon) noexcept {
    return std::abs(moon.velocity.x_velocity) + std::abs(moon.velocity.y_velocity) + std::abs(moon.velocity.z_velocity);
}

int get_total_energy(const Moon& moon) noexcept {
    return get_potential_energy(moon) * get_kinetic_energy(moon);
}

