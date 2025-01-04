#include <fstream>
#include <iostream>
#include <queue>
#include <regex>
#include <string>
#include <utility>
#include <vector>
#include <climits>

int GRID_SIZE = 71; // extra one because of zero indexing

std::vector<std::string> grid;
std::vector<std::pair<int, int>> corruptedBytes;

std::vector<int> getNumbersFromString(const std::string& string) {
    std::vector<int> numbers;
    std::regex pattern("\\d+");

    std::sregex_iterator begin(string.begin(), string.end(), pattern);
    std::sregex_iterator end;

    for (std::sregex_iterator it = begin; it != end; it++) {
        numbers.push_back(std::stoi(it->str()));
    }

    return numbers;
}

const std::vector<std::pair<int, int>> directions = {
    {0, 1},
    {1, 0},
    {0, -1},
    {-1, 0}
};

int dijkstra() {
    std::vector<std::vector<int>> distance(GRID_SIZE, std::vector<int>(GRID_SIZE, INT_MAX));
    distance[0][0] = 0;

    std::priority_queue<std::pair<int, std::pair<int, int>>,
                        std::vector<std::pair<int, std::pair<int, int>>>,
                        std::greater<>> pq;

    pq.push({0, {0, 0}});

    while (!pq.empty()) {
        auto [currentDistance, currentPosition] = pq.top();
        pq.pop();

        int x = currentPosition.first;
        int y = currentPosition.second;

        if (x == GRID_SIZE - 1 && y == GRID_SIZE - 1) {
            return currentDistance;
        }

        if (currentDistance > distance[y][x]) {
            continue;
        }

        for (const auto& dir : directions) {
            int newX = x + dir.first;
            int newY = y + dir.second;

            if (newX >= 0 && newX < GRID_SIZE && newY >= 0 && newY < GRID_SIZE && grid[newY][newX] == '.') {
                int newDistance = currentDistance + 1;

                if (newDistance < distance[newY][newX]) {
                    distance[newY][newX] = newDistance;
                    pq.push({newDistance, {newX, newY}});
                }
            }
        }
    }

    return 0;
}

int main() {
    std::ifstream puzzle_input("puzzle_input.txt");

    if (!puzzle_input.is_open()) {
        std::cerr << "Error: Could not open file 'puzzle_input.txt'" << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(puzzle_input, line)) {
        std::vector<int> numbers = getNumbersFromString(line);
        if (numbers.size() == 2) {
            corruptedBytes.emplace_back(numbers[0], numbers[1]);
        }
    }

    grid.resize(GRID_SIZE, std::string(GRID_SIZE, '.'));
    for (int i = 0; i < 1024; i++) {
        int x = corruptedBytes[i].first;
        int y = corruptedBytes[i].second;

        if (x >= 0 && x < GRID_SIZE && y >= 0 && y < GRID_SIZE) {
            grid[y][x] = '#';
        }
    }

    for (int i = 1024; i < corruptedBytes.size(); i++) {
        int x = corruptedBytes[i].first;
        int y = corruptedBytes[i].second;

        if (x >= 0 && x < GRID_SIZE && y >= 0 && y < GRID_SIZE) {
            grid[y][x] = '#';
        }

        if (dijkstra() == 0) {
            std::cout << x << "," << y << std::endl;
            break;
        }
    }

    return 0;
}

