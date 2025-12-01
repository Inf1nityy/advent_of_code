#include <cctype>
#include <cstdint>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <set>

std::vector<std::vector<int>> getGaps(const std::map<int, int>& map) {
    std::vector<std::vector<int>> segments;
    std::vector<int> gaps;
    int prev_key = -1;

    for (const auto& pair : map) {
        int cur_key = pair.first;
        if (cur_key > prev_key + 1) {
            if (!gaps.empty()) {
                segments.push_back(gaps);
                gaps.clear();
            }

            for (int i = prev_key + 1; i < cur_key; i++) {
                gaps.push_back(i);
            }
        }
        prev_key = cur_key;
    }

    if (!gaps.empty()) {
        segments.push_back(gaps);
    }

    return segments;
}

std::vector<int> getKeysWithId(int id, const std::map<int, int>& map) {
    std::vector<int> keys;

    for (const auto& element : map) {
        if (element.second == id) {
            keys.push_back(element.first);
        }
    }

    return keys;
}

int main() {
    std::ifstream puzzle_input("puzzle_input.txt");

    std::map<int, int> checkSum;
    int id = 0;
    int cur = 0;
    std::string line;

    while (std::getline(puzzle_input, line)) {
        for (int i = 0; i < line.size(); i++) {
            int digit = line[i] - '0';
            if (i % 2 == 0) {
                for (int j = 0; j < digit; j++) {
                    checkSum[cur + j] = id;
                }
                id++;
            }
            cur += digit;
        }
    }

    std::set<int> ids;
    for (const auto& element : checkSum) {
        ids.insert(element.second);
    }

    std::set<int, std::greater<int>> uniqueIds(ids.begin(), ids.end());

    for (int id : uniqueIds) {
        std::vector<int> keys = getKeysWithId(id, checkSum);

        for (const std::vector<int>& gap : getGaps(checkSum)) {
            if (gap.size() >= keys.size() && gap[0] < keys[0]) {
                for (int i = 0; i < keys.size(); i++) {
                    checkSum[gap[i]] = id;
                    checkSum.erase(keys[i]);
                }
                break;
            }
        }
    }

    int64_t result = 0;
    for (const auto& element : checkSum) {
        result += element.first * element.second;
    }

    std::cout << "Result: " << result << std::endl;
    return 0;
}

