#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <ostream>
#include <vector>

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

    std::sort(first_row.begin(), first_row.end());
    std::sort(second_row.begin(), second_row.end());

    int sum = 0;
    for (int i = 0; i < first_row.size(); i++) {
        sum += abs(first_row[i] - second_row[i]);
    }

    std::cout << sum << std::endl;
}
