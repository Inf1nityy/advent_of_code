#include <bits/stdc++.h>
#include <exception>
#include <string>
using namespace std;

string line;
string operations;
long result = 0;

void part1() {
    vector<vector<long>> grid;
    while (getline(cin, line)) {
        if (line.find("*") != string::npos) {
            line.erase(remove(line.begin(), line.end(), ' '), line.end());
            operations = line;
            continue;
        }

        istringstream iss(line);

        long tmp;
        vector<long> numberList;
        while (iss >> tmp) {
            numberList.push_back(tmp);
        }

        grid.push_back(numberList);
    }

    long num = 0;
    for (int i = 0; i < grid[0].size(); i++) {
        for (int j = 0; j < grid.size(); j++) {
            if (operations[i] == '*') {
                if (num == 0) {
                    num = grid[j][i];
                } else {
                    num *= grid[j][i];
                }
            } else {
                num += grid[j][i];
            }
        }

        result += num;
        num = 0;
    }

    cout << result << endl;
}

void part2() {
    vector<string> grid;
    char lastOperator = ' ';

    while (getline(cin, line)) {
        if (line.find("*") != string::npos) {
            operations = line;
            continue;
        }

        grid.push_back(line);
    }

    vector<long> nums;
    for (int i = 0; i < grid[0].length(); i++) {
        string num = "";
        for (int j = 0; j < grid.size(); j++) {
            num += grid[j][i];
        }

        try {
            nums.push_back(stoll(num));
        } catch (exception e) {
            nums.push_back(-1);
        }
    }

    long tmp = 0;
    for (int i = 0; i < operations.length(); i++) {
        if (operations[i] != ' ') {
            lastOperator = operations[i];
            result += tmp;
            tmp = lastOperator == '*' ? 1 : 0;
        }

        if (nums[i] == -1) continue;

        if (lastOperator == '*') {
            tmp *= nums[i];
        } else {
            tmp += nums[i];
        }
    }

    result += tmp;
    tmp = 0;

    cout << result << endl;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: ./day06 <1|2>\n";
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
