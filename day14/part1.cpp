#include <utility>
#include <vector>
#include <regex>
#include <fstream>
#include <iostream>
#include <algorithm>

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

	for (int t = 0; t < 100; t++) {
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
	}

	int quadrantOne = std::count_if(robots.begin(), robots.end(), [](Robot robot) {
        return robot.position.first < (GRID_WIDTH - 1) / 2 && robot.position.second < (GRID_HEIGHT - 1) / 2;
    });

	int quadrantTwo = std::count_if(robots.begin(), robots.end(), [](Robot robot) {
        return robot.position.first > (GRID_WIDTH - 1) / 2 && robot.position.second < (GRID_HEIGHT - 1) / 2;
    });

    int quadrantThree = std::count_if(robots.begin(), robots.end(), [](Robot robot) {
        return robot.position.first < (GRID_WIDTH - 1) / 2 && robot.position.second > (GRID_HEIGHT - 1) / 2;
    });

	int quadrantFour = std::count_if(robots.begin(), robots.end(), [](Robot robot) {
        return robot.position.first > (GRID_WIDTH - 1) / 2 && robot.position.second > (GRID_HEIGHT - 1) / 2;
    });

	std::cout << "Result: " << quadrantOne * quadrantTwo * quadrantThree * quadrantFour << "\n";
}