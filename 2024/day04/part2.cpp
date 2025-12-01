#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <vector>

std::vector<std::string> grid = {};

bool validCoord(int x, int y) {
    if (x >= 0 && x < grid.size() && y >= 0 && y < grid[0].size())
        return true;
    return false;
}

bool checkLeftDiagonal(int x, int y) {
    std::string wordToCheck = "";

    for (int move = -1; move <= 1; move++) {
        if (validCoord(x + move, y + move))
            wordToCheck += grid[x + move][y + move];
    }

    if (wordToCheck.find("MAS") != std::string::npos || wordToCheck.find("SAM") != std::string::npos) {
        return true;
    }

    return false;
}

bool checkRightDiagonal(int x, int y) {
    std::string wordToCheck = "";

    for (int move = -1; move <= 1; move++) {
        if (validCoord(x + move, y + move))
            wordToCheck += grid[x + move][y - move];
    }

    if (wordToCheck.find("MAS") != std::string::npos || wordToCheck.find("SAM") != std::string::npos) {
        return true;
    }

    return false;
}

int searchWord(std::string word) {
    int wordCount = 0;
    std::vector<std::pair<int, int>> directions = {
        {-1, -1}, {-1, 1}, {1, 1}, {1, -1}
    };

    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            if (grid[i][j] == 'A') {
                if(checkLeftDiagonal(i, j) && checkRightDiagonal(i, j))
                    wordCount++;
            }
        }
    }

    return wordCount;
}

int main() {
    std::ifstream puzzle_input("puzzle_input.txt");

    std::string line;
    while (std::getline(puzzle_input, line)) {
        grid.push_back(line);
    }

    std::cout << searchWord("MAS") << std::endl;
}
