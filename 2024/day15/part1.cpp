#include <string>
#include <fstream>
#include <vector>
#include <utility>
#include <iostream>

std::pair<int, int> robotPosition = {};
std::vector<std::string> grid = {};
std::string movementInstructions = {};

std::pair<int, int> getOffset(char movementInstruction) {
    switch (movementInstruction) {
        case '<': return {0, -1};
        case '>': return {0, 1};
        case '^': return {-1, 0};
        case 'v': return {1, 0};
    }
    return {0, 0};
}

std::vector<std::pair<int, int>> getMovableBoxes(std::pair<int, int> boxPosition, const std::pair<int, int>& offset, std::vector<std::pair<int, int>> movableBoxes) {
	std::pair<int, int> newPosition = std::make_pair(boxPosition.first + offset.first, boxPosition.second + offset.second);

	if (grid[newPosition.first][newPosition.second] == '.') {
		movableBoxes.push_back(boxPosition);
		return movableBoxes;
	} else if (grid[newPosition.first][newPosition.second] == 'O') {
		movableBoxes.push_back(boxPosition);
		return getMovableBoxes(newPosition, offset, movableBoxes);
	}

	return {};
}

int main() {
	std::ifstream puzzle_input("puzzle_input.txt");

	std::string line;
	int i = 0;
	while (std::getline(puzzle_input, line)) {
		if (line.starts_with("#")) {
			grid.push_back(line);
			for (int j = 0; j < line.size(); j++) {
				if (grid[i][j] == '@') {
					robotPosition = std::make_pair(i, j);
				}
			}

			i++;
		} else if (!line.empty()) {
			line.erase(std::remove(line.begin(), line.end(), '\n'), line.cend());
			movementInstructions += line;
		}
	}

	for (char movementInstruction : movementInstructions) {
		std::pair<int, int> offset = getOffset(movementInstruction);

		int ni = robotPosition.first + offset.first;
		int nj = robotPosition.second + offset.second;

		if (grid[ni][nj] == '.') {
			std::swap(grid[ni][nj], grid[robotPosition.first][robotPosition.second]);
			robotPosition = std::make_pair(ni, nj);
		} else if (grid[ni][nj] == 'O') {
			std::vector<std::pair<int, int>> movableBoxes = getMovableBoxes({ni, nj}, offset, {});

			if (!movableBoxes.empty()) {
				for (auto it = movableBoxes.rbegin(); it != movableBoxes.rend(); it++) {
					std::pair<int, int> newPosition = std::make_pair(it->first + offset.first, it->second + offset.second);
					std::swap(grid[newPosition.first][newPosition.second], grid[it->first][it->second]);
				}

				std::swap(grid[ni][nj], grid[robotPosition.first][robotPosition.second]);
				robotPosition = std::make_pair(ni, nj);
			}
		}
	}

	int result = 0;
	for (int i = 0; i < grid.size(); i++) {
		for (int j = 0; j < grid[i].size(); j++) {
			if (grid[i][j] == 'O') {
				result += 100 * i + j;
			}
		}
	}

	std::cout << "Result: " << result << "\n";
}