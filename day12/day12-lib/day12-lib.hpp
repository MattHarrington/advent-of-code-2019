#pragma once

#include <vector>

struct Position {
    int x;
    int y;
    int z;
};

struct Velocity {
    int x_velocity;
    int y_velocity;
    int z_velocity;
};

struct Moon {
    Position position;
    Velocity velocity;
};

bool operator== (const Moon lhs, const Moon rhs) noexcept;

bool operator== (const Position lhs, const Position rhs) noexcept;

bool operator== (const Velocity lhs, const Velocity rhs) noexcept;

std::vector<Moon> timestep(const std::vector<Moon>& moons);

int get_potential_energy(const Moon& moon) noexcept;

int get_kinetic_energy(const Moon& moon) noexcept;

int get_total_energy(const Moon& moon) noexcept;

