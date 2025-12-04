#include <bits/stdc++.h>
#include <string>
using namespace std;

vector<string> grid;
int result = 0;
vector<pair<int, int>> offsets = {
    {-1, 0}, {1, 0}, {0, 1}, {0, -1},
    {1, 1}, {1, -1}, {-1, 1}, {-1, -1}
};

void createGrid() {
    string line;
    while (getline(cin, line)) {
        if (line.empty()) continue;
        grid.push_back(line);
    }
}

int findAccessiblePaperRolls() {
    int num = 0;

    for (int x = 0; x < grid.size(); x++) {
        for (int y = 0; y < grid[x].size(); y++) {
            if (grid[x][y] != '@') continue;

            int neighbourRolls = 0;
            for (auto offset : offsets) {
                int offsetX = x + offset.first;
                int offsetY = y + offset.second;

                if (offsetX < 0 || offsetX >= grid.size() || offsetY < 0 || offsetY >= grid[x].size()) 
                    continue;

                if (grid[offsetX][offsetY] == '@') neighbourRolls++;
            }

            if (neighbourRolls < 4) {
                grid[x][y] = 'x';
                result++;
                num++;
            }
        }
    }

    return num;
}

void part1() {
    createGrid();

    for (int x = 0; x < grid.size(); x++) {
        for (int y = 0; y < grid[x].size(); y++) {
            if (grid[x][y] != '@') continue;

            int neighbourRolls = 0;
            for (auto offset : offsets) {
                int offsetX = x + offset.first;
                int offsetY = y + offset.second;

                if (offsetX < 0 || offsetX >= grid.size() || offsetY < 0 || offsetY >= grid[x].size()) 
                    continue;

                if (grid[offsetX][offsetY] == '@') neighbourRolls++;
            }

            if (neighbourRolls < 4) {
                result++;
            }
        }
    }

    cout << result << endl;
}

void part2() {
    createGrid();

    while (findAccessiblePaperRolls() != 0) {

    }

    cout << result << endl;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: ./day03 <1|2>\n";
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
