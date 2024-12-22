#include <fstream>
#include <string>
#include <utility>
#include <vector>
#include <regex>
#include <iostream>
#include <cmath>

struct ClawMachine {
    std::pair<int, int> buttonA = {};
    std::pair<int, int> buttonB = {};
    std::pair<int, int> prize = {};
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
int solveLinearEquations(const std::pair<int, int>& buttonA, const std::pair<int, int>& buttonB, const std::pair<int, int>& prize) {
    double determinant = buttonA.first * buttonB.second - buttonA.second * buttonB.first;

    if (determinant == 0) {
        return 0;
    }

    double y = (buttonA.first * prize.second - buttonA.second * prize.first) / determinant;
    double x = (prize.first * buttonB.second - prize.second * buttonB.first) / determinant;

    return (x > 100 || y > 100 || x <= 0 || y <= 0 || std::fmod(x, 1.0) != 0 || std::fmod(y, 1.0) != 0) ? 0 : 3*x + y;
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
            clawMachine.prize = std::make_pair(numbers[0], numbers[1]);
        } else if (line.empty()) {
            clawMachines.push_back(clawMachine);
            clawMachine = ClawMachine();
        }
    }

    clawMachines.push_back(clawMachine); // have to include this because the last line isn't empty

    int result = 0;
    for (auto clawMachine : clawMachines) {
        result += solveLinearEquations(clawMachine.buttonA, clawMachine.buttonB, clawMachine.prize);
    }

    std::cout << "Result: " << result << "\n";
}
