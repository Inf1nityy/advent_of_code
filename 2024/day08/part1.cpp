#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <set>
#include <string>
#include <utility>
#include <vector>

class Antenna {
    public:
    char frequency;
    int x;
    int y;
    Antenna(char frequency, int x, int y) {
        this->frequency = frequency;
        this->x = x;
        this->y = y;
    }
};

std::vector<Antenna> antennas = {};
std::set<char> frequencies = {};
std::pair<int, int> gridBounds = {};

bool outOfBounds(int x, int y) {
    return x < 0 || x >= gridBounds.first || y < 0 || y >= gridBounds.second;
}

int main() {
    std::ifstream puzzle_input("puzzle_input.txt");

    std::string line;
    int lineWidth = 0;
    int lineNumber = 0;
    while (std::getline(puzzle_input, line)) {
        for (int i = 0; i < line.size(); i++) {
            char character = line[i];
            if (character != '.' && character != '#') {
                antennas.push_back(Antenna(character, i, lineNumber));
                frequencies.insert(character);
            }
        }

        lineNumber++;
        lineWidth = line.size();
    }
    gridBounds = {lineWidth, lineNumber};

    std::set<std::pair<int, int>> uniqueAntinodes;
    for (char frequency : frequencies) {
        auto predicate = [&frequency](Antenna i){ return i.frequency == frequency; };
        std::vector<Antenna> matchingAntennas;
        std::copy_if(antennas.begin(), antennas.end(), std::back_inserter(matchingAntennas), predicate);

        for (int i = 0; i < matchingAntennas.size(); i++) {
            for (int j = i + 1; j < matchingAntennas.size(); j++) {
                Antenna antennaOne = matchingAntennas[i];
                Antenna antennaTwo = matchingAntennas[j];

                int dx = antennaTwo.x - antennaOne.x;
                int dy = antennaTwo.y - antennaOne.y;

                int antinodeOneX = antennaOne.x - dx;
                int antinodeOneY = antennaOne.y - dy;

                int antinodeTwoX = antennaTwo.x + dx;
                int antinodeTwoY = antennaTwo.y + dy;

                if (!outOfBounds(antinodeOneX, antinodeOneY)) {
                    uniqueAntinodes.insert({antinodeOneX, antinodeOneY});
                }

                if (!outOfBounds(antinodeTwoX, antinodeTwoY)) {
                    uniqueAntinodes.insert({antinodeTwoX, antinodeTwoY});
                }
            }
        }
    }

    std::cout << "Result: " << uniqueAntinodes.size() << std::endl;
}
