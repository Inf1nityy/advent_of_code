#include <cstdlib>
#include <fstream>
#include <set>
#include <string>
#include <vector>
#include <utility>
#include <climits>
#include <iostream>

std::vector<std::string> grid = {};
std::pair<int, int> start = {};
std::pair<int, int> end = {};

int main() {
    std::ifstream puzzle_input("puzzle_input.txt");

    int i = 0;
    std::string line;
    while (std::getline(puzzle_input, line)) {
        grid.push_back(line);
        for (int j = 0; j < line.size(); j++) {
            if (line[j] == 'S') {
                start = {i, j};
            } else if (line[j] == 'E') {
                end = {i, j};
            }
        }

        i++;
    }

    auto [r, c] = start;
    std::vector<std::vector<int>> distances(grid.size(), std::vector<int>(grid[0].size(), -1));
    distances[r][c] = 0;

    while (grid[r][c] != 'E') {
        for (const auto& [nr, nc] : std::vector<std::pair<int, int>>{{r + 1, c}, {r - 1, c}, {r, c + 1}, {r, c - 1}}) {
            if (nr < 0 || nc < 0 || nr >= grid.size() || nc >= grid[0].size()) continue;
            if (grid[nr][nc] == '#') continue;
            if (distances[nr][nc] != -1) continue;

            distances[nr][nc] = distances[r][c] + 1;
            r = nr;
            c = nc;
        }
    }

    int count = 0;
    for (int r = 0; r < grid.size(); r++) {
        for (int c = 0; c < grid[0].size(); c++) {
            if (grid[r][c] == '#') continue;

            for (int radius = 2; radius < 21; radius++) {
                for (int dr = 0; dr < radius + 1; dr++) {
                    int dc = radius - dr;
                    for (const auto& [nr, nc] : std::set<std::pair<int, int>>{{r + dr, c + dc}, {r + dr, c - dc}, {r - dr, c + dc}, {r - dr, c - dc}}) {
                        if (nr < 0 || nc < 0 || nr >= grid.size() || nc >= grid[0].size()) continue;
                        if (grid[nr][nc] == '#') continue;

                        if (distances[r][c] - distances[nr][nc] >= 100 + radius) count++;
                    }
                }
            }
        }
    }

    std::cout << "Result: " << count << std::endl;

    return 0;
}
