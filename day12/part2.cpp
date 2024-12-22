#include <map>
#include <string>
#include <utility>
#include <vector>
#include <iostream>
#include <fstream>

std::vector<std::string> grid = {};
std::vector<std::vector<bool>> visited = {};
std::vector<std::pair<int, int>> offsets = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
std::vector<std::pair<double, double>> corners = {{0.5, 0.5}, {0.5, -0.5}, {-0.5, 0.5}, {-0.5, -0.5}};

struct Region {
    int area;
    char plant;
    std::map<std::pair<double, double>, std::vector<std::pair<double, double>>> vertices = {};

    Region(int area, char plant) {
        this->area = area;
        this->plant = plant;
    }

    int getNumberOfSides() {
        int numberOfSides = 0;

        for (auto& [key, value] : this->vertices) {
            if (value.size() == 1 || value.size() == 3) {
                numberOfSides++;
            } else if (value.size() == 2 && value[0].first != value[1].first && value[0].second != value[1].second) {
                numberOfSides += 2;
            }
        }

        return numberOfSides;
    }
};

bool outOfBounds(int x, int y) {
    return y < 0 || y >= grid.size() || x < 0 || x >= grid[y].size();
}

void dfs(int i, int j, Region& region) {
    visited[i][j] = true;
    region.area++;

    for (auto& diagonal : corners) {
        double newI = i + diagonal.first;
        double newJ = j + diagonal.second;

        region.vertices[{newI, newJ}].push_back(std::make_pair(i, j));
    }

    for (auto& offset : offsets) {
        int newI = i + offset.first;
        int newJ = j + offset.second;

        if (!outOfBounds(newI, newJ) && grid[newI][newJ] == region.plant) {
            if (!visited[newI][newJ]) {
                dfs(i + offset.first, j + offset.second, region);
            }
        }
    }
}

int main() {
    std::vector<Region> regions = {};
    std::ifstream puzzle_input("puzzle_input.txt");

    std::string line;
    while (std::getline(puzzle_input, line)) {
        grid.push_back(line);
    }

    visited.resize(grid.size());
    for (int i = 0; i < grid.size(); i++) {
        visited[i].resize(grid[i].size(), false);
    }

    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            if (visited[i][j]) continue;

            Region newRegion = Region(0, grid[i][j]);

            dfs(i, j, newRegion);
            regions.push_back(newRegion);
        }
    }

    int result = 0;
    for (auto region : regions) {
        result += region.area * region.getNumberOfSides();
    }

    std::cout << "Result: " << result << std::endl;
}
