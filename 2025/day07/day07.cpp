#include <bits/stdc++.h>
using namespace std;

long result = 0;
string line;
vector<string> grid;
pair<int, int> startingPos;
map<pair<int, int>, bool> checked;

void move(pair<int, int> pos) {
    if (pos.first < 0 || pos.first >= grid.size()) return;
    if (pos.second < 0 || pos.second >= grid[0].size()) return;

    if (checked.find(pos) != checked.end()) return;
    checked.insert({pos, true});

    int newY = pos.first + 1;

    if (newY < 0 || newY >= grid.size()) return;

    if (grid[newY][pos.second] == '.') {
        move({newY, pos.second});
    } else if (grid[newY][pos.second] == '^') {
        result++;

        if (pos.second - 1 >= 0)
            move({newY, pos.second - 1});

        if (pos.second + 1 < grid[newY].size())
            move({newY, pos.second + 1});
    }
}

void createGrid() {
    while (getline(cin, line)) {
        if (line.empty()) continue;

        size_t startingX = line.find("S");
        int i = 0;
        if (startingX != string::npos) {
            startingPos = pair(i, startingX);
            i++;
        }

        grid.push_back(line);
    }
}

void part1() {
    createGrid();    
    move(startingPos);
    cout << result << endl;
}

void part2() {
    createGrid();

    vector<vector<long>> dp(grid.size(), vector<long>(grid[0].size(), 0));
    dp[startingPos.first][startingPos.second] = 1;

    for (int r = startingPos.first; r + 1 < grid.size(); r++) {
        for (int c = 0; c < grid[0].size(); c++) {
            long timelines = dp[r][c];
            if (timelines == 0) continue;

            char below = grid[r + 1][c];

            if (below == '.') {
                dp[r + 1][c] += timelines;
            }
            else if (below == '^') {
                if (c - 1 >= 0) dp[r + 1][c - 1] += timelines;
                if (c + 1 < grid[0].size()) dp[r + 1][c + 1] += timelines;
            }
        }
    }

    for (int c = 0; c < grid[0].size(); c++) {
        result += dp[grid.size() - 1][c];
    }

    cout << result << endl;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: ./day07 <1|2>\n";
        return 1;
    }

    int part = stoi(argv[1]);

    if (part == 1) {
        part1();
    } else if (part == 2) {
        part2();
    } else {
        cerr << "Part must be 1 or 2\n";
        return 1;
    }

    return 0;
}
