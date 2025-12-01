#include <fstream>
#include <limits>
#include <vector>
#include <string>
#include <queue>
#include <iostream>

std::vector<std::string> grid = {};
std::vector<std::pair<int, int>> offsets = {{0, 1}, {-1, 0}, {0, -1}, {1, 0}};

bool is90DegreeRotation(const std::pair<int, int>& offset1, const std::pair<int, int>& offset2) {
    return (offset1.first == -offset2.second && offset1.second == offset2.first) || 
           (offset1.first == offset2.second && offset1.second == -offset2.first);
}

int main() {
    std::ifstream puzzle_input("puzzle_input.txt");

    std::pair<int, int> startingPosition = {};
    std::pair<int, int> endingPosition = {};
    int rows = 0;

    std::string line;
    while (std::getline(puzzle_input, line)) {
        grid.push_back(line);

        for (int j = 0; j < grid[rows].size(); j++) {
            if (grid[rows][j] == 'S') {
                startingPosition = {rows, j};
            } else if (grid[rows][j] == 'E') {
                endingPosition = {rows, j};
            }
        }
        rows++;
    }

    int cols = grid[0].size();
    std::vector<std::vector<int>> score(rows, std::vector<int>(cols, std::numeric_limits<int>::max()));
    std::vector<std::vector<std::pair<int, int>>> previousOffset(rows, std::vector<std::pair<int, int>>(cols, {0, 0}));
    std::priority_queue<std::tuple<int, int, int, int, int>, std::vector<std::tuple<int, int, int, int, int>>, std::greater<>> pq;
    pq.push({0, startingPosition.first, startingPosition.second, 0, 0});

    score[startingPosition.first][startingPosition.second] = 0;

    while (!pq.empty()) {
        auto [currentScore, x, y, currentRotations, prevDir] = pq.top();
        pq.pop();

        if (x == endingPosition.first && y == endingPosition.second) {
            std::cout << "Result: " << currentScore << std::endl;
            break;
        }

        for (size_t i = 0; i < offsets.size(); i++) {
            int nx = x + offsets[i].first;
            int ny = y + offsets[i].second;

            if (nx >= 0 && nx < rows && ny >= 0 && ny < cols) {
                int newScore = currentScore;
                bool validMove = false;

                if (i == prevDir) {
                    newScore += 1;
                    validMove = true;
                } else if (is90DegreeRotation(offsets[i], offsets[prevDir])) {
                    newScore += 1001;
                    validMove = true;
                }

                if (validMove && grid[nx][ny] != '#') {
                    if (newScore < score[nx][ny]) {
                        score[nx][ny] = newScore;
                        pq.push({newScore, nx, ny, currentRotations + (i != prevDir), i});
                    }
                }
            }
        }
    }

}
