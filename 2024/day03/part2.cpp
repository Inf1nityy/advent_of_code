#include <iostream>
#include <regex>
#include <fstream>
#include <string>

int multiply(std::string string) {
    int result = 1;
    std::regex pattern("\\d+");

    std::sregex_iterator begin(string.begin(), string.end(), pattern);
    std::sregex_iterator end;

    for (std::sregex_iterator it = begin; it != end; ++it) {
        result *= std::stoi(it->str());
    }

    return result;
}

int main() {
    std::ifstream puzzle_input("puzzle_input.txt");

    bool shouldMultiply = true;
    int result = 0;
    std::string line;
    while (std::getline(puzzle_input, line)) {
        std::regex pattern("mul\\(\\d+,\\d+\\)|do\\(\\)|don't\\(\\)");

        std::sregex_iterator begin(line.begin(), line.end(), pattern);
        std::sregex_iterator end;

        for (std::sregex_iterator it = begin; it != end; ++it) {
            std::string string = it->str();
            if (string == "don't()") {
                shouldMultiply = false;
            } else if (string == "do()") {
                shouldMultiply = true;
            } else {
                if (shouldMultiply) {
                    result += multiply(string);
                }
            }
        }
    }

    std::cout << result << std::endl;
}

