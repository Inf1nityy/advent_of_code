#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

std::vector<int> getDifferences(std::vector<int> numbers) {
    std::vector<int> differences = {};
    for (int i = 0; i < numbers.size(); i++) {
        if ((i - 1) >= 0) {
            differences.push_back(numbers[i] - numbers[i - 1]);
        }
    }

    return differences;
}

int main() {
    std::ifstream puzzle_input("puzzle_input.txt");

    int safeReports = 0;
    std::string line;
    while (std::getline(puzzle_input, line)) {
        std::vector<int> numbers = {};
        int num;

        std::istringstream stream(line);
        while (stream >> num) {
            numbers.push_back(num);
        }

        std::vector<int> differences = getDifferences(numbers);

        bool safe = true;

        bool allPositive = std::all_of(differences.begin(), differences.end(), [](int n) { return n > 0; });
        bool allNegative = std::all_of(differences.begin(), differences.end(), [](int n) { return n < 0; });

        if (allPositive == false && allNegative == false) {
            continue;
        }

        for (int i = 0; i < differences.size(); i++) {
            if (abs(differences[i]) > 3 || abs(differences[i]) < 1) {
                safe = false;
                break;
            }
        }

        if (safe) {
            safeReports++;
        }
    }

    std::cout << safeReports << std::endl;
}
