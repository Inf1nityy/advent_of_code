#include <cstdint>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <functional>
#include <cmath>
#include <string>

using Operator = std::function<uint64_t(uint64_t, uint64_t)>;
Operator add = [](uint64_t a, uint64_t b) { return a + b; };
Operator mul = [](uint64_t a, uint64_t b) { return a * b; };
Operator concatenation = [](uint64_t a, std::uint64_t b) {
    return std::stoull(std::to_string(a).append(std::to_string(b)));
};

void generateOperatorCombinations(int length, std::vector<std::vector<Operator>>& combinations) {
    std::vector<Operator> ops = {add, mul, concatenation};
    int totalCombos = std::pow(ops.size(), length);

    for (int i = 0; i < totalCombos; ++i) {
        std::vector<Operator> combo;
        int current = i;

        for (int j = 0; j < length; ++j) {
            combo.push_back(ops[current % ops.size()]);
            current /= ops.size();
        }

        combinations.push_back(combo);
    }
}

bool checkCanEqual(const std::vector<uint64_t>& numbers, uint64_t target) {
    int n_ops = numbers.size() - 1;
    std::vector<std::vector<Operator>> operatorCombos;

    generateOperatorCombinations(n_ops, operatorCombos);

    for (const auto& ops : operatorCombos) {
        uint64_t result = numbers[0];
        for (int i = 0; i < ops.size(); ++i) {
            result = ops[i](result, numbers[i + 1]);
        }

        if (result == target) {
            return true;
        }
    }

    return false;
}

int main() {
    std::ifstream file("puzzle_input.txt");
    std::string line;
    std::vector<std::pair<uint64_t, std::vector<uint64_t>>> equations;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string left, right;

        std::getline(iss, left, ':');
        std::getline(iss, right);

        uint64_t target = std::stoull(left);
        std::istringstream seqStream(right);
        std::vector<uint64_t> numbers;
        uint64_t num;

        while (seqStream >> num) {
            numbers.push_back(num);
        }

        equations.push_back({target, numbers});
    }

    uint64_t total = 0;
    for (const auto& [target, numbers] : equations) {
        if (checkCanEqual(numbers, target)) {
            total += target;
        }
    }

    std::cout << "Result: " << total << std::endl;
    return 0;
}

