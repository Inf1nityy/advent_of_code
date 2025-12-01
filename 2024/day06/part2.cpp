#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

std::vector<std::string> grid = {};

enum guardDirection {
    NORTH, EAST, SOUTH, WEST
};
std::pair<int, int> guardPosition = {};
std::pair<int, int> offset;
guardDirection currentGuardDirection;
std::vector<std::vector<bool>> visited = {};

void rotateGuard() {
    switch (currentGuardDirection) {
        case NORTH:
            currentGuardDirection = EAST;
            offset = {0, 1};
            break;
        case EAST:
            currentGuardDirection = SOUTH;
            offset = {1, 0};
            break;
        case SOUTH:
            currentGuardDirection = WEST;
            offset = {0, -1};
            break;
        case WEST:
            currentGuardDirection = NORTH;
            offset = {-1, 0};
            break;
    }
}

bool solveCycle(std::vector<std::string> grid) {
    int rotations = 0;

    while (true) {
        rotations++;
        std::pair<int, int> newPosition = {guardPosition.first + offset.first, guardPosition.second + offset.second};

        if (rotations == 10000) {
            return true;
        }

        if (newPosition.first < 0 || newPosition.first >= grid.size()) return false;
        if (newPosition.second < 0 || newPosition.second >= grid[newPosition.first].size()) return false;

        if (grid[newPosition.first][newPosition.second] == '#') {
            rotateGuard();
        } else {
            guardPosition = newPosition;
        }
    }
}

void setup() {
    visited.clear();
    grid.clear();

    offset = {-1, 0};
    currentGuardDirection = NORTH;
    std::ifstream puzzle_input("puzzle_input.txt");

    std::string line;
    int lineNumber = 0;
    while (getline(puzzle_input, line)) {
        for (int i = 0; i < line.size(); i++) {
            if (line[i] == '^') {
                guardPosition = {lineNumber, i};
            }
        }

        grid.push_back(line);
        lineNumber++;
    }

    visited.resize(grid.size());
    for (int i = 0; i < grid.size(); i++) {
        visited[i].resize(grid[i].size(), false);
    }
    visited[guardPosition.first][guardPosition.second] = true;
}

int main() {
    setup();

    std::pair<int, int> startingGuard = guardPosition;

    int answer = 0;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            if (grid[i][j] == '.' && std::make_pair(i, j) != guardPosition) {
                grid[i][j] = '#';
                
                if (solveCycle(grid)) {
                    answer++;
                }

                guardPosition = startingGuard;
                currentGuardDirection = NORTH;
                offset = {-1, 0};

                grid[i][j] = '.';
            }
        }
    }

    std::cout << "Result: " << answer << std::endl;
}
