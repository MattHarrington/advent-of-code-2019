// https://adventofcode.com/2019/day/12#part2

#ifndef day12_lib_h
#define day12_lib_h

#include <vector>

struct Position {
    int x;
    int y;
    int z;
    bool operator==(const Position&) const noexcept;
};

struct Velocity {
    int x_velocity;
    int y_velocity;
    int z_velocity;
    bool operator==(const Velocity&) const noexcept;
};

struct Moon {
    Position position;
    Velocity velocity;
    bool operator==(const Moon&) const noexcept;
};

std::vector<Moon> timestep(const std::vector<Moon>& moons);

int get_potential_energy(const Moon& moon) noexcept;

int get_kinetic_energy(const Moon& moon) noexcept;

int get_total_energy(const Moon& moon) noexcept;

#endif

