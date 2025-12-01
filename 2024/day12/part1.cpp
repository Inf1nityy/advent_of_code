#include <string>
#include <vector>
#include <iostream>
#include <fstream>

std::vector<std::string> grid = {};
std::vector<std::vector<bool>> visited = {};
std::vector<std::pair<int, int>> offsets = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

struct Region {
    int area;
    int perimeter;
    char plant;

    Region(int area, int perimeter, char plant) {
        this->area = area;
        this->perimeter = perimeter;
        this->plant = plant;
    }
};

bool outOfBounds(int x, int y) {
    return y < 0 || y >= grid.size() || x < 0 || x >= grid[y].size();
}

void dfs(int i, int j, Region& region) {
    visited[i][j] = true;
    region.area++;

    for (auto& offset : offsets) {
        int newI = i + offset.first;
        int newJ = j + offset.second;

        if (!outOfBounds(newI, newJ) && grid[newI][newJ] == region.plant) {
            if (!visited[newI][newJ]) {
                dfs(i + offset.first, j + offset.second, region);
            }
        } else {
            region.perimeter++;
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

            Region newRegion = Region(0, 0, grid[i][j]);

            dfs(i, j, newRegion);
            regions.push_back(newRegion);
        }
    }

    int result = 0;
    for (auto region : regions) {
        result += region.area * region.perimeter;
    }

    std::cout << "Result: " << result << std::endl;
}
