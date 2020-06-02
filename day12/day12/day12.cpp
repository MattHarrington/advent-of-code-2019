// https://adventofcode.com/2019/day/12

#include <cassert>
#include <iostream>
#include <numeric>
#include "day12-lib.h"

int main() {
    std::vector<Moon> moons{
        Moon{ {12,0,-15},  {0,0,0} },
        Moon{ {-8,-5,-10}, {0,0,0} },
        Moon{ {7,-17,1},   {0,0,0} },
        Moon{ {2,-11,-6},  {0,0,0} }
    };

    for (int i{ 0 }; i < 1000; ++i) {
        moons = timestep(moons);
    }

    const int part1_answer{ std::accumulate(begin(moons), end(moons), 0, [](int t, Moon m) {return t + get_total_energy(m); }) };
    std::cout << "part1_answer: " << part1_answer << "\n";
    assert(part1_answer == 7636);
}

