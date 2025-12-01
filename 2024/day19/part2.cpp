#include <cstdint>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iostream>
#include <regex>
#include <unordered_map>

uint64_t countArrangements(const std::string& pattern, const std::vector<std::string>& strings, std::unordered_map<std::string, uint64_t>& memo) {
    if (memo.find(pattern) != memo.end()) {
        return memo[pattern];
    }

    if (pattern.empty()) {
        return 1;
    }

    uint64_t count = 0;

    for (const auto& str : strings) {
        if (pattern.find(str) == 0) {
            count += countArrangements(pattern.substr(str.size()), strings, memo);
        }
    }

    memo[pattern] = count;
    return count;
}

std::vector<std::string> splitString(const std::string& str, char delimiter) {
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string token;

    while (std::getline(ss, token, delimiter)) {
        result.push_back(token);
    }

    return result;
}

int main() {
    std::ifstream puzzle_input("puzzle_input.txt");

    uint64_t result = 0;
    std::string line;
    std::vector<std::string> strings = {};
    std::unordered_map<std::string, uint64_t> memo;
    while (std::getline(puzzle_input, line)) {
        if (line.find(',') != std::string::npos) {
            line = std::regex_replace(line, std::regex(" "), "");
            strings = splitString(line, ',');
        }

        if (line.empty()) continue;
        result += countArrangements(line, strings, memo);
    }

    std::cout << "Result: " << result << std::endl;

    return 0;
}
