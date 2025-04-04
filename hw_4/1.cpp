#include <fstream>
#include <cassert>
#include <string>

#include <algorithm>
#include <array>
#include <iterator>
#include <random>
#include <vector>

#include <iostream>
#include <format>

// generator of random lines
void random_file(const std::string& filename, int num_lines, int line_length) {
    std::fstream wstream(filename, std::ios::out);
    assert(wstream.is_open() == 1);

    std::vector< int > vec(10, 0);

    // generate random numbers
    std::array < std::random_device::result_type, std::mt19937_64::state_size > seed_data{};

    // generate seeds
    std::random_device rd;
    std::ranges::generate(seed_data, std::ref(rd));

    std::seed_seq seq{ std::begin(seed_data), std::end(seed_data) };

    // initialize the generator
    std::mt19937_64 gen(seq);
    //readable symbols
    std::uniform_int_distribution<> dis(32, 126);

    for (int i = 0; i < num_lines; ++i) {
        std::string str;
        str.reserve(line_length);
        for (int j = 0; j < line_length; ++j) {
            str += static_cast<char>(dis(gen));
        }
        wstream << str << '\n';
    }
}

int main() {
    //name for txt
    const std::string filename = "num_1.txt";
    //amount, length of lines
    const int N = 100, L = 50;

    // call function
    random_file(filename, N, L);

    // Main part
    int line_number{};
    std::cout << "Enter line number (first index is 0): ";
    std::cin >> line_number;

    std::fstream rstream(filename, std::ios::in);
    assert(rstream.is_open() == 1);

    std::string buffer{};
    //2 bytes for '\n'
    rstream.seekg(line_number * (L + 2));
    std::getline(rstream, buffer);

    std::cout << std::format("Index {} of line: {}", line_number, buffer) << std::endl;
}