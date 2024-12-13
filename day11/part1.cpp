#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

std::vector<int> stones = {};

void blink(int numberOfBlinks) {
    for (int i = 0; i < stones.size(); i++) {
        if (stones[i] == 0) {
            stones[i] = 1;
            continue;
        }

        std::string stoneString = std::to_string(stones[i]);
        if (stoneString.size() % 2 == 0) {
            std::string firstHalf = stoneString.substr(0, stoneString.size() / 2);
            std::string secondHalf = stoneString.substr(stoneString.size() / 2);

            stones[i] = std::stoi(firstHalf);
            stones.insert(stones.begin() + i + 1, std::stoi(secondHalf));

            i++;
            continue;
        }

        stones[i] = stones[i] * 2024;
    }

    if (numberOfBlinks == 25) {
        return;
    }

    numberOfBlinks++;
    blink(numberOfBlinks);
}

int main() {
    std::ifstream puzzle_input("puzzle_input.txt");
    std::string line;
    std::getline(puzzle_input, line);

    std::istringstream iss(line);
    int number;

    while (iss >> number) {
        stones.push_back(number);
    }

    blink(1);
    std::cout << "Result: " << stones.size() << std::endl;
}