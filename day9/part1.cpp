#include <algorithm>
#include <cctype>
#include <cstdint>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <utility>

std::map<int, int> checkSum = {};

int main() {
    std::ifstream puzzle_input("puzzle_input.txt");

    int id = 0;
    int cur = 0;
    std::string line;
    while (std::getline(puzzle_input, line)) {
        for (int i = 0; i < line.size(); i++) {
            int digit = line[i] - '0';
            if (i % 2 == 0) {
                for (int j = 0; j < digit; j++) {
                    checkSum[cur + j] = id;
                }

                id++;
            }
            cur += digit;
        }
    }

    int pos = 0;
    while (true) {
        auto max_iter = std::max_element(checkSum.begin(), checkSum.end(),
                                         [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
                                             return a.first < b.first;
                                         });
        int rm = max_iter->first;
        int id = max_iter->second;
        
        checkSum.erase(rm);
        
        while (checkSum.count(pos)) {
            pos++;
        }
        
        checkSum[pos] = id;
        
        if (pos == rm) {
            break;
        }
    }

    int64_t result = 0;

    for (auto element : checkSum) {
        result += element.first * element.second;
    }

    std::cout << "Result: " << result << std::endl;
}
