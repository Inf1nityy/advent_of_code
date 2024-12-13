#include <iostream>
#include <fstream>
#include <vector>

int result = 0;
std::vector<std::vector<int>> grid;
std::vector<std::pair<int, int>> offsets = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};

void getGrid() {
    std::ifstream puzzle_input("puzzle_input.txt");
    std::string line;

    while (std::getline(puzzle_input, line)) {
        std::vector<int> numbers;
        for (char character : line) {
            numbers.push_back(character - '0');
        }
        grid.push_back(numbers);
    }
}

bool outOfBounds(int x, int y) {
    return y < 0 || y >= grid.size() || x < 0 || x >= grid[0].size();
}

void getNumberOfTrails(int x, int y, int element, std::vector<std::vector<bool>>& visited) {
    if (visited[y][x]) return;
    visited[y][x] = true;

    if (element == 9) {
        result += 1;
        return;
    }

    for (const auto& offset : offsets) {
        int newX = x + offset.first;
        int newY = y + offset.second;

        if (!outOfBounds(newX, newY) && grid[newY][newX] == element + 1) {
            getNumberOfTrails(newX, newY, element + 1, visited);
        }
    }
}

int main() {
    getGrid();

    for (int y = 0; y < grid.size(); y++) {
        for (int x = 0; x < grid[0].size(); x++) {
            if (grid[y][x] == 0) {
                std::vector<std::vector<bool>> visited(grid.size(), std::vector<bool>(grid[0].size(), false));
                getNumberOfTrails(x, y, 0, visited);
            }
        }
    }

    std::cout << "Result: " << result << std::endl;
    return 0;
}
