#include <cstdlib>
#include <iostream>
#include <fstream>
#include <ostream>
#include <vector>

int getNumberOfRepeats(std::vector<int> vector, int element) {
    int repeating = 0;
    for (int integer : vector) {
        if (integer == element) {
            repeating++;
        }
    }

    return repeating;
}

int main() {
    std::ifstream puzzle_input;
    puzzle_input.open("puzzle_input.txt");

    std::vector<int> first_row;
    std::vector<int> second_row;

    int a, b;
    while (puzzle_input >> a >> b) {
        first_row.push_back(a);
        second_row.push_back(b);
    }

    int similarityScore = 0;
    for (int i = 0; i < first_row.size(); i++) {
        similarityScore += first_row[i] * getNumberOfRepeats(second_row, first_row[i]);
    }

    std::cout << similarityScore << std::endl;
}

