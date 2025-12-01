#include <algorithm>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <string>
#include <vector>
#include <sstream>

std::unordered_map<std::string, std::unordered_set<std::string>> computers;
std::set<std::vector<std::string>> sets; // Store sorted connections as a key

std::vector<std::string> splitString(const std::string& str, char delimiter) {
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string token;

    while (std::getline(ss, token, delimiter)) {
        result.push_back(token);
    }

    return result;
}

void search(const std::string& node, std::unordered_set<std::string> req) {
    std::vector<std::string> key(req.begin(), req.end());
    std::sort(key.begin(), key.end());

    if (sets.find(key) != sets.end()) return;
    sets.insert(key);

    for (const auto& neighbor : computers[node]) {
        if (req.find(neighbor) != req.end()) continue;

        bool valid = true;
        for (const auto& query : req) {
            if (computers[query].find(neighbor) == computers[query].end()) {
                valid = false;
                break;
            }
        }
        if (!valid) continue;

        auto newReq = req;
        newReq.insert(neighbor);
        search(neighbor, newReq);
    }
}

int main() {
    std::ifstream puzzle_input("puzzle_input.txt");

    std::string line;
    while (std::getline(puzzle_input, line)) {
        auto connection = splitString(line, '-');
        computers[connection[0]].insert(connection[1]);
        computers[connection[1]].insert(connection[0]);
    }

    for (const auto& node : computers) {
        search(node.first, {node.first});
    }

    std::vector<std::string> biggestSet;
    for (const auto& s : sets) {
        if (s.size() > biggestSet.size()) {
            biggestSet = s;
        }
    }

    for (size_t i = 0; i < biggestSet.size(); ++i) {
        std::cout << biggestSet[i];
        if (i != biggestSet.size() - 1) {
            std::cout << ",";
        }
    }
    std::cout << std::endl;

    return 0;
}

