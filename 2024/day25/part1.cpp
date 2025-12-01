#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::vector<int>> keys = {};
std::vector<std::vector<int>> locks = {};

int main() {
    std::ifstream puzzle_input("puzzle_input.txt");
    std::vector<std::vector<std::string>> schematics = {};

    std::string line;
    std::vector<std::string> schematic = {};
    while (std::getline(puzzle_input, line)) {
        if (line[0] == '.' || line[0] == '#') {
            schematic.push_back(line);
        } else if (line.empty()) {
            schematics.push_back(schematic);
            schematic.clear();
        }
    }

    for (auto schematic : schematics) {
        std::vector<int> heights = {0, 0, 0, 0, 0};
        for (int i = 1; i < schematic.size() - 1; i++) {
            for (int j = 0; j < schematic[i].size(); j++) {
                if (schematic[i][j] == '#') {
                    heights[j]++;
                }
            }
        }

        if (schematic[0] == "#####" && schematic[6] == ".....") {
            locks.push_back(heights);
        } else if (schematic[0] == "....." && schematic[6] == "#####") {
            keys.push_back(heights);
        }
    }

    int result = 0;
    for (auto lock : locks) {
        for (auto key : keys) {
            bool doesFit = true;

            for (int i = 0; i < 5; i++) {
                if (key[i] + lock[i] > 5) {
                    doesFit = false;
                    break;
                }
            }

            if (doesFit) result++;
        }
    }

    std::cout << "Result: " << result << std::endl;
}
