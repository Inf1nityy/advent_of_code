#include <iostream>
#include <fstream>
#include <list>
#include <unordered_map>

int get_calibration_value(std::string line) {
    std::unordered_map<std::string, std::string> numbers = {
        {"one", "1"},
        {"two", "2"},
        {"three", "3"},
        {"four", "4"},
        {"five", "5"},
        {"six", "6"},
        {"seven", "7"},
        {"eight", "8"},
        {"nine", "9"}
    };

    for (auto number : numbers) {
        while (line.find(number.first) != std::string::npos) {
            line.replace(line.find(number.first) + 1, 1, number.second);
        }
    }

    std::cout << line << std::endl;

    int first_digit = 69;
    int second_digit;

    for (char character : line) {
        if (std::isdigit(character)) {
            if (first_digit == 69) {
                first_digit = int(character - 48);
                second_digit = first_digit;
            } else {
                second_digit = int(character - 48);
            }
        }
    }

    return first_digit * 10 + second_digit;
}

int main(void) {
    std::string line;
    std::ifstream puzzle_input("puzzle_input.txt");
    std::list<int> numbers = {};

    if (puzzle_input.is_open()) {
        while (std::getline(puzzle_input, line)) {
            std::cout << get_calibration_value(line) << std::endl;
            numbers.push_back(get_calibration_value(line));
        }
        puzzle_input.close();
    }

    int sum = 0;
    for (int number : numbers) {
        sum += number;
    }

    std::cout << sum << std::endl;
}
