#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

std::vector<int> getDifferences(const std::vector<int>& numbers) {
    std::vector<int> differences;
    for (size_t i = 1; i < numbers.size(); ++i) {
        differences.push_back(numbers[i] - numbers[i - 1]);
    }
    return differences;
}

bool isSafe(const std::vector<int>& numbers) {
    if (numbers.size() < 2) return false;

    std::vector<int> differences = getDifferences(numbers);

    bool allPositive = std::all_of(differences.begin(), differences.end(), [](int n) { return n > 0; });
    bool allNegative = std::all_of(differences.begin(), differences.end(), [](int n) { return n < 0; });

    if (!allPositive && !allNegative) return false;

    for (int diff : differences) {
        if (abs(diff) > 3 || abs(diff) < 1) {
            return false;
        }
    }

    return true;
}

int main() {
    std::ifstream puzzle_input("puzzle_input.txt");

    if (!puzzle_input.is_open()) {
        std::cerr << "Failed to open the file!" << std::endl;
        return 1;
    }

    int safeReports = 0;
    std::string line;
    while (std::getline(puzzle_input, line)) {
        std::vector<int> numbers;
        std::istringstream stream(line);
        int num;
        while (stream >> num) {
            numbers.push_back(num);
        }

        if (isSafe(numbers)) {
            safeReports++;
            continue;
        }

        bool foundSafeAfterRemoval = false;
        for (size_t i = 0; i < numbers.size(); ++i) {
            std::vector<int> modifiedNumbers = numbers;
            modifiedNumbers.erase(modifiedNumbers.begin() + i);

            if (isSafe(modifiedNumbers)) {
                foundSafeAfterRemoval = true;
                break;
            }
        }

        if (foundSafeAfterRemoval) {
            safeReports++;
        }
    }

    std::cout << "Safe reports: " << safeReports << std::endl;

    return 0;
}
