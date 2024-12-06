#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <unordered_map>
#include <vector>

std::unordered_map<int, std::vector<int>> pageOrdering = {};

std::vector<int> getNumbersFromString(std::string string) {
    std::vector<int> numbers = {};
    std::regex pattern("\\d+");

    std::sregex_iterator begin(string.begin(), string.end(), pattern);
    std::sregex_iterator end;

    for (std::sregex_iterator it = begin; it != end; it++) {
        numbers.push_back(std::stoi(it->str()));
    }

    return numbers;
}

bool appearsBefore(int element1, int element2, std::vector<int> update) {
    int elementIndex1 = -1;
    int elementIndex2 = -1;

    for (int i = 0; i < update.size(); i++) {
        if (update[i] == element1 && elementIndex1 == -1) elementIndex1 = i;
        if (update[i] == element2 && elementIndex2 == -1) elementIndex2 = i;
    }

    if (elementIndex1 == -1 || elementIndex2 == -1) return false;
    return elementIndex1 < elementIndex2;
}

bool isRightOrder(std::vector<int> update) {
    for (int element : update) {
        if (pageOrdering.find(element) == pageOrdering.end()) {
            continue;
        }

        for (int pageOrder : pageOrdering[element]) {
            if (std::find(update.begin(), update.end(), pageOrder) == update.end()) {
                continue;
            }

            if (!appearsBefore(element, pageOrder, update)) {
                return false;
            }
        }
    }

    return true;
}

int getMiddleNumber(std::vector<int> numbers) {
    return numbers[numbers.size() / 2];
}

int main() {
    int result = 0;
    std::ifstream puzzle_input("puzzle_input.txt");

    std::string line;
    while (std::getline(puzzle_input, line)) {
        std::vector<int> numbers = getNumbersFromString(line);

        if (line.find("|") != std::string::npos) {
            pageOrdering[numbers[0]].push_back(numbers[1]);
        } 

        else if (line.find(",") != std::string::npos) {
            if (isRightOrder(numbers)) {
                result += getMiddleNumber(numbers);
            }
        }
    }

    std::cout << "Result: " << result << std::endl;
}
