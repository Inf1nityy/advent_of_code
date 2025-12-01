#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iostream>
#include <regex>

bool canConstruct(const std::string& pattern, const std::vector<std::string>& strings) {
    int n = pattern.size();
    std::vector<bool> dp(n + 1, false);
    dp[0] = true;

    for (int i = 0; i <= n; ++i) {
        if (!dp[i]) continue;
        for (const auto& str : strings) {
            int len = str.size();
            if (i + len <= n && pattern.substr(i, len) == str) {
                dp[i + len] = true;
            }
        }
    }

    return dp[n];
}

std::vector<std::string> splitString(const std::string& str, char delimiter) {
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string token;

    while (std::getline(ss, token, delimiter)) {
        result.push_back(token);
    }

    return result;
}

int main() {
    std::ifstream puzzle_input("puzzle_input.txt");

    int result = 0;
    std::string line;
    std::vector<std::string> strings = {};
    while (std::getline(puzzle_input, line)) {
        if (line.find(',') != std::string::npos) {
            line = std::regex_replace(line, std::regex(" "), "");
            strings = splitString(line, ',');
        }

        if (line.empty()) continue;
        if (canConstruct(line, strings)) {
            result++;
        }
    }

    std::cout << "Result: " << result << std::endl;

    return 0;
}
