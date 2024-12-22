#include <fstream>
#include <string>
#include <utility>
#include <vector>
#include <regex>
#include <iostream>
#include <cmath>

struct ClawMachine {
    std::pair<long, long> buttonA = {};
    std::pair<long, long> buttonB = {};
    std::pair<long, long> prize = {};
};

std::vector<ClawMachine> clawMachines = {};

std::vector<int> extractIntegers(const std::string& string) {
    std::vector<int> numbers = {};
    std::regex pattern("\\d+");

    std::sregex_iterator begin(string.begin(), string.end(), pattern);
    std::sregex_iterator end;

    for (std::sregex_iterator it = begin; it != end; it++) {
        numbers.push_back(std::stoi(it->str()));
    }

    return numbers;
}

// Wait what.... math?
long solveLinearEquations(const std::pair<long, long>& buttonA, const std::pair<long, long>& buttonB, const std::pair<long, long>& prize) {
    long double determinant = buttonA.first * buttonB.second - buttonA.second * buttonB.first;

    if (determinant == 0) {
        return 0;
    }

    long double y = (buttonA.first * prize.second - buttonA.second * prize.first) / determinant;
    long double x = (prize.first * buttonB.second - prize.second * buttonB.first) / determinant;

    return (x <= 0 || y <= 0 || std::fmodl(x, 1.0) != 0 || std::fmodl(y, 1.0) != 0) ? 0 : 3*x + y;
}

int main() {
    std::ifstream puzzle_input("puzzle_input.txt");

    std::string line;
    ClawMachine clawMachine = ClawMachine();
    while (std::getline(puzzle_input, line)) {
        if (line.starts_with("Button A")) {
            auto numbers = extractIntegers(line);
            clawMachine.buttonA = std::make_pair(numbers[0], numbers[1]);
        } else if (line.starts_with("Button B")) {
            auto numbers = extractIntegers(line);
            clawMachine.buttonB = std::make_pair(numbers[0], numbers[1]);
        } else if (line.starts_with("Prize")) {
            auto numbers = extractIntegers(line);
            clawMachine.prize = std::make_pair(numbers[0] + 10000000000000, numbers[1] + 10000000000000);
        } else if (line.empty()) {
            clawMachines.push_back(clawMachine);
            clawMachine = ClawMachine();
        }
    }

    clawMachines.push_back(clawMachine); // have to include this because the last line isn't empty

    long result = 0;
    for (auto clawMachine : clawMachines) {
        result += solveLinearEquations(clawMachine.buttonA, clawMachine.buttonB, clawMachine.prize);
    }

    std::cout << "Result: " << result << "\n";
}