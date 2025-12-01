#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>
#include <sstream>

std::unordered_map<std::string, std::vector<std::string>> computers = {};
std::set<std::tuple<std::string, std::string, std::string>> interconnected = {};

std::vector<std::string> splitString(const std::string& str, char delimiter) {
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string token;

    while (std::getline(ss, token, delimiter)) {
        result.push_back(token);
    }

    return result;
}

bool areConnected(const std::string& comp1, const std::string& comp2) {
    const auto& neighbors1 = computers[comp1];
    return std::find(neighbors1.begin(), neighbors1.end(), comp2) != neighbors1.end();
}

void checkInterconnectedComputers() {
    for (auto& comp1 : computers) {
        for (auto& comp2 : comp1.second) {
            for (auto& comp3 : computers) {
                if (comp3.first != comp1.first && comp3.first != comp2) {
                    if (areConnected(comp1.first, comp2) && 
                        areConnected(comp2, comp3.first) && 
                        areConnected(comp1.first, comp3.first)) {

                        std::vector<std::string> triplet = {comp1.first, comp2, comp3.first};
                        std::sort(triplet.begin(), triplet.end());
                        interconnected.insert(std::make_tuple(triplet[0], triplet[1], triplet[2]));
                    }
                }
            }
        }
    }
}

bool hasT(const std::tuple<std::string, std::string, std::string>& triplet) {
    return (std::get<0>(triplet)[0] == 't' || std::get<1>(triplet)[0] == 't' || std::get<2>(triplet)[0] == 't');
}

int main() {
    std::ifstream puzzle_input("puzzle_input.txt");

    std::string line;
    while (std::getline(puzzle_input, line)) {
        auto connection = splitString(line, '-');

        computers[connection[0]].push_back(connection[1]);
        computers[connection[1]].push_back(connection[0]);
    }

    checkInterconnectedComputers();

    int count = 0;
    for (const auto& triplet : interconnected) {
        if (hasT(triplet)) {
            count++;
        }
    }

    std::cout << "Result: " << count << std::endl;

    return 0;
}

