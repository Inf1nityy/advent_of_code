#include <cmath>
#include <csignal>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>

uint64_t registerA = 0;
uint64_t registerB = 0;
uint64_t registerC = 0;
std::vector<int> program = {};
std::vector<int> output = {};

int instructionPointer = 0;

uint64_t comboOperand(int operand) {
    switch (operand) {
        case 0: case 1: case 2: case 3: return operand;
        case 4: return registerA;
        case 5: return registerB;
        case 6: return registerC;
        default: return -1;
    }
}

void executeInstruction(int opcode, int operand) {
    switch (opcode) {
        case 0:
            instructionPointer += 2;
            registerA = registerA >> comboOperand(operand);
            break;
        case 1:
            instructionPointer += 2;
            registerB ^= operand;
            break;
        case 2:
            instructionPointer += 2;
            registerB = comboOperand(operand) % 8;
            break;
        case 3:
            (registerA != 0) ? instructionPointer = operand : instructionPointer += 2;
            break;
        case 4:
            instructionPointer += 2;
            registerB ^= registerC;
            break;
        case 5:
            instructionPointer += 2;
            output.push_back(comboOperand(operand) % 8);
            break;
        case 6:
            instructionPointer += 2;
            registerB = registerA >> comboOperand(operand);
            break;
        case 7:
            instructionPointer += 2;
            registerC = registerA >> comboOperand(operand);
            break;
    }
}

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

int main() {
    std::ifstream puzzle_input("puzzle_input.txt");
    std::string line;

    while (std::getline(puzzle_input, line)) {
        std::vector<int> numbers = getNumbersFromString(line);

        if (line.starts_with("Register A")) {
            registerA = numbers[0];
        } else if (line.starts_with("Register B")) {
            registerB = numbers[0];
        } else if (line.starts_with("Register C")) {
            registerC = numbers[0];
        } else if (line.starts_with("Program")) {
            program = numbers;
        }
    }

    while (instructionPointer < program.size()) {
        executeInstruction(program[instructionPointer], program[instructionPointer + 1]);
    }


    for (int i = 0; i < output.size(); i++) {
        std::cout << output[i];
        if (i != output.size() - 1) {
            std::cout << ",";
        }
    }
    std::cout << std::endl;
}
