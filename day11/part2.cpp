#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>
#include <cmath>

std::unordered_map<long, long> stoneMap = {};

void blink(int numberOfBlinks) {
    if (numberOfBlinks == 0) {
        return;
    }

    std::unordered_map<long, long> newStoneMap = {};

    for (auto& element : stoneMap) {
        if (element.first == 0) {
            newStoneMap[1] += element.second;
            continue;
        }

        std::string stoneString = std::to_string(element.first);
        if (stoneString.size() % 2 == 0) {
            std::string firstHalf = stoneString.substr(0, stoneString.size() / 2);
            std::string secondHalf = stoneString.substr(stoneString.size() / 2);           

            newStoneMap[std::stol(firstHalf)] += element.second;
            newStoneMap[std::stol(secondHalf)] += element.second;
        } else {
            newStoneMap[element.first * 2024] += element.second;
        }
    }

    stoneMap = newStoneMap;


    blink(numberOfBlinks - 1);
}

int main() {
    std::ifstream puzzle_input("puzzle_input.txt");
    std::string line;
    std::getline(puzzle_input, line);

    std::istringstream iss(line);
    int number;

    while (iss >> number) {
        stoneMap[number]++;
    }

    blink(75);

    long result = 0;
    for (auto& element : stoneMap) {
        result += element.second;
    }

    std::cout << "Result: " << result << std::endl;
}