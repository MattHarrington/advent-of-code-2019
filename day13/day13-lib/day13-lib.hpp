#ifndef DAY13_LIB_HPP
#define DAY13_LIB_HPP

constexpr size_t PROGRAM_SIZE{ 1'000'000 };

enum class opcode {
    add = 1, multiply, input, output, jump_if_true, jump_if_false, less_than, equals, adjust_offset, halt = 99
};

enum class mode {
    position, immediate, relative
};

struct Program {
    std::vector<long long> intcodes;
    size_t ip;
    size_t offset;
    std::queue<int> input;
};

std::vector<long long> get_intcodes(std::string filename);

std::queue<long long> process(Program& p);

#endif

