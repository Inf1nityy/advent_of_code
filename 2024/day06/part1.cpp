#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>
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

void printScreen() {
    system("clear");
    for (std::string string : grid) {
        std::cout << string << std::endl;
    }

    std::cout << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
}

int getWalkedPositions() {
    int walkedPositions = 1; // this is one because it has to include starting position

    while (true) {
        std::pair<int, int> newPosition = {guardPosition.first + offset.first, guardPosition.second + offset.second};

        if (newPosition.first < 0 || newPosition.first >= grid.size()) break;
        if (newPosition.second < 0 || newPosition.second >= grid[newPosition.first].size()) break;

        if (grid[newPosition.first][newPosition.second] == '#') {
            rotateGuard();
        } else {
            if (!visited[newPosition.first][newPosition.second]) {
                walkedPositions++;
                visited[newPosition.first][newPosition.second] = true;
            }

            grid[guardPosition.first][guardPosition.second] = 'X';
            grid[newPosition.first][newPosition.second] = '^';
            guardPosition = newPosition;
        }

        //printScreen();
    }

    return walkedPositions;
}

int main() {
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

    std::cout << "Result: " << getWalkedPositions() << std::endl;
}
