#include <cmath>
#include <cstdint>
#include <fstream>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>

struct VectorHash {
    std::size_t operator()(const std::vector<int>& vec) const {
        std::size_t seed = 0;
        for (int num : vec) {
            seed ^= std::hash<int>{}(num) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;
    }
};

std::unordered_map<std::vector<int>, int, VectorHash> sequenceToTotal;

uint64_t step(uint64_t num) {
    num = (num ^ (num * 64)) % 16777216;
    num = (num ^ (num / 32)) % 16777216;
    num = (num ^ (num * 2048)) % 16777216;
    return num;
}

int main() {
    std::ifstream puzzle_input("puzzle_input.txt");
    std::string line;

    std::vector<uint64_t> initialSecrets;
    while (std::getline(puzzle_input, line)) {
        initialSecrets.push_back(std::stoull(line));
    }

    for (uint64_t num : initialSecrets) {
        int initialDigit = num % 10;
        std::vector<int> buyer = {initialDigit};

        for (int i = 0; i < 2000; ++i) {
            num = step(num);
            buyer.push_back(num % 10);
        }

        std::set<std::vector<int>> seen;

        for (size_t i = 0; i <= buyer.size() - 5; ++i) {
            int a = buyer[i];
            int b = buyer[i + 1];
            int c = buyer[i + 2];
            int d = buyer[i + 3];
            int e = buyer[i + 4];

            std::vector<int> sequence = {b - a, c - b, d - c, e - d};

            if (seen.find(sequence) != seen.end()) continue;

            seen.insert(sequence);

            sequenceToTotal[sequence] += e;
        }
    }

    int biggestPrice = 0;
    for (const auto& pair : sequenceToTotal) {
        if (pair.second > biggestPrice) {
            biggestPrice = pair.second;
        }
    }

    std::cout << "Result: " << biggestPrice << std::endl;
    return 0;
}

