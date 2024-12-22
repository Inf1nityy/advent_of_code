#include <utility>
#include <vector>
#include <regex>
#include <fstream>
#include <iostream>
#include <set>

class Robot {
	public:
		std::pair<int, int> position;
		std::pair<int, int> velocity;

		Robot(std::pair<int, int> position, std::pair<int, int> velocity) {
			this->position = position;
			this->velocity = velocity;
		}
};

int GRID_HEIGHT = 103;
int GRID_WIDTH = 101;
std::vector<Robot> robots = {};

bool allPositionsUnique() {
    std::set<std::pair<int, int>> uniquePositions;
    for (const auto& robot : robots) {
        uniquePositions.insert(robot.position);
    }
    return uniquePositions.size() == robots.size();
}

std::vector<int> extractIntegers(const std::string& string) {
    std::vector<int> numbers = {};
    std::regex pattern("-?\\d+");

    std::sregex_iterator begin(string.begin(), string.end(), pattern);
    std::sregex_iterator end;

    for (std::sregex_iterator it = begin; it != end; it++) {
        numbers.push_back(std::stoi(it->str()));
    }

    return numbers;
}

int main() {
	std::ifstream puzzle_input("puzzle_input.txt");

	std::string line;
	while (std::getline(puzzle_input, line)) {
		std::vector<int> numbers = extractIntegers(line);
		robots.push_back(Robot(std::make_pair(numbers[0], numbers[1]), std::make_pair(numbers[2], numbers[3])));
	}

	int seconds = 0;
	while (!allPositionsUnique()) {
		for (Robot& robot : robots) {
			int nx = robot.position.first + robot.velocity.first;
			int ny = robot.position.second + robot.velocity.second;

			if (ny < 0) {
				ny = ny + GRID_HEIGHT;
			}

			if (ny >= GRID_HEIGHT) {
				ny = ny - GRID_HEIGHT;
			}

			if (nx < 0) {
				nx = nx + GRID_WIDTH;
			}

			if (nx >= GRID_WIDTH) {
				nx = nx - GRID_WIDTH;
			}

			robot.position = std::make_pair(nx, ny);
		}

		seconds++;
	}

	std::cout << "Result: " << seconds << std::endl;
}