#include <string>
#include <fstream>
#include <vector>
#include <utility>
#include <iostream>
#include <algorithm>

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

int main() {
	std::ifstream puzzle_input("puzzle_input.txt");

	std::string line;
	while (std::getline(puzzle_input, line)) {
		if (line.starts_with("#")) {
			std::string scaledRow = "";
			for (char tile : line) {
	            if (tile == '#') scaledRow += "##";
	            else if (tile == 'O') scaledRow += "[]";
	            else if (tile == '.') scaledRow += "..";
	            else if (tile == '@') scaledRow += "@.";
	        }

	        grid.push_back(scaledRow);
		} else if (!line.empty()) {
			line.erase(std::remove(line.begin(), line.end(), '\n'), line.cend());
			movementInstructions += line;
		}
	}

	for (int i = 0; i < grid.size(); i++) {
		for (int j = 0; j < grid[i].size(); j++) {
			if (grid[i][j] == '@') {
				robotPosition = std::make_pair(i, j);
			}
		}
	}

	for (char movementInstruction : movementInstructions) {
		std::pair<int, int> offset = getOffset(movementInstruction);

		std::vector<std::pair<int, int>> targets = {robotPosition};
		bool go = true;
		for (int i = 0; i < targets.size(); i++) {
			int nr = targets[i].first + offset.first;
			int nc = targets[i].second + offset.second;

			if (std::find(targets.begin(), targets.end(), std::make_pair(nr, nc)) != targets.end()) continue;

			char tile = grid[nr][nc];

			if (tile == '#') {
				go = false;
				break;
			}

			if (tile == '[') {
				targets.push_back({nr, nc});
				targets.push_back({nr, nc + 1});
			}

			if (tile == ']') {
				targets.push_back({nr, nc});
				targets.push_back({nr, nc - 1});
			}
		}

		if (!go) continue;

		grid[robotPosition.first][robotPosition.second] = '.';
		robotPosition = {robotPosition.first + offset.first, robotPosition.second + offset.second};
		auto copiedGrid = grid;

		for (auto it = targets.begin() + 1; it != targets.end(); it++) {
	        grid[it->first][it->second] = '.';
	    }

	    for (auto it = targets.begin() + 1; it != targets.end(); it++) {
	        grid[it->first + offset.first][it->second + offset.second] = copiedGrid[it->first][it->second];
	    }

		grid[robotPosition.first][robotPosition.second] = '@';
	}

	int result = 0;
	for (int i = 0; i < grid.size(); i++) {
		for (int j = 0; j < grid[i].size(); j++) {
			if (grid[i][j] == '[') {
				result += 100 * i + j;
			}
		}
	}

	std::cout << "Result: " << result << "\n";
}