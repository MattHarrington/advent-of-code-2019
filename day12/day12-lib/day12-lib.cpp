// https://adventofcode.com/2019/day/12

#include <cmath>
#include "day12-lib.h"

bool Position::operator==(const Position& other) const noexcept {
    return x == other.x && y == other.y && z == other.z;
}

bool Velocity::operator==(const Velocity& other) const noexcept {
    return x_velocity == other.x_velocity && y_velocity == other.y_velocity
        && z_velocity == other.z_velocity;
}

bool Moon::operator==(const Moon& other) const noexcept {
    return position == other.position && velocity == other.velocity;
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

