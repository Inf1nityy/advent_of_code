#include <cmath>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

uint64_t step(uint64_t num) {
    num = (num ^ (num * 64)) % 16777216;
    num = (num ^ (num / 32)) % 16777216;
    num = (num ^ (num * 2048)) % 16777216;
    return num;
}

int main() {
    std::vector<int> initialSecrets = {};
    std::ifstream puzzle_input("puzzle_input.txt");

    std::string line;
    while (std::getline(puzzle_input, line)) {
        initialSecrets.push_back(std::stoi(line));
    }

    uint64_t result = 0;
    for (uint64_t secret : initialSecrets) {
        for (int i = 0; i < 2000; i++) {
            secret = step(secret);
        }
        result += secret;
    }

    std::cout << "Result: " << result << std::endl;
    return 0;
}

