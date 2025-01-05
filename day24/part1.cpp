#include <fstream>
#include <queue>
#include <regex>
#include <string>
#include <unordered_map>
#include <iostream>

std::unordered_map<std::string, int> variables = {};
std::queue<std::string> instructions = {};

std::vector<std::string> splitString(const std::string& str, char delimiter) {
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string token;

    while (std::getline(ss, token, delimiter)) {
        result.push_back(token);
    }

    return result;
}

bool isValidVariable(std::string variable) {
    return variables.count(variable) > 0;
}

int main() {
    std::ifstream puzzle_input("puzzle_input.txt");

    std::string line;
    while (std::getline(puzzle_input, line)) {
        if (line.find(": ") != std::string::npos) {
            line = std::regex_replace(line, std::regex(" "), "");
            auto strings = splitString(line, ':');
            variables[strings[0]] = std::stoi(strings[1]);
        } else if (!line.empty()) {
            instructions.push(line);
        }
    }

    while (!instructions.empty()) {
        std::string instruction = instructions.front();
        instructions.pop();

        std::vector<std::string> parsedInstruction = splitString(instruction, ' ');
        if (!isValidVariable(parsedInstruction[0]) || !isValidVariable(parsedInstruction[2])) {
            instructions.push(instruction);
        } else {
            int a = variables[parsedInstruction[0]];
            int b = variables[parsedInstruction[2]];

            if (parsedInstruction[1] == "AND") {
                variables[parsedInstruction[4]] = a && b;
            } else if (parsedInstruction[1] == "XOR") {
                variables[parsedInstruction[4]] = a ^ b;
            } else if (parsedInstruction[1] == "OR") {
                variables[parsedInstruction[4]] = a || b;
            }
        }
    }

    std::vector<std::string> keys;
    for (const auto& pair : variables) {
        if (pair.first[0] == 'z') {
            keys.push_back(pair.first);
        }
    }

    std::sort(keys.begin(), keys.end(), [](const std::string& a, const std::string& b) {
        return a > b;
    });

    std::string binaryNumber;
    for (const std::string& key : keys) {
        if (variables.find(key) != variables.end()) {
            binaryNumber += std::to_string(variables[key]);
        }
    }

    unsigned long result = std::bitset<64>(binaryNumber).to_ulong();
    std::cout << "Result: " << result << std::endl;
}
