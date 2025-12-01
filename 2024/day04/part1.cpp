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


bool findWord(int index, std::string word, int x, int y, int dx, int dy) {
    if (index == word.length()) return true;
    
    if (validCoord(x, y) && word[index] == grid[x][y])
        return findWord(index + 1, word, x + dx, y + dy, dx, dy);
        
    return false;
}

int searchWord(std::string word) {
    int wordCount = 0;
    std::vector<std::pair<int, int>> directions = {
        {-1, 0}, {0, 1}, {1, 0}, {0, -1}, 
        {-1, -1}, {-1, 1}, {1, 1}, {1, -1}
    };

    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            for (int k = 0; k < 8; k++) {
                if (findWord(0, word, i, j, directions[k].first, directions[k].second)) {
                    wordCount++;
                }
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

    std::cout << searchWord("XMAS") << std::endl;
}
