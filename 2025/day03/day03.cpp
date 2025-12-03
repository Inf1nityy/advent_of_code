#include <bits/stdc++.h>
#include <string>
using namespace std;

long long solve(int k) {
    string line;
    long long result = 0;

    while (getline(cin, line)) {
        int n = line.size();
        vector<char> stack;

        for (int i = 0; i < n; i++) {
            char c = line[i];

            while (!stack.empty() && stack.back() < c && stack.size() + (n - i - 1) >= k) {
                stack.pop_back();
            }

            if (stack.size() < k) {
                stack.push_back(c);
            }
        }

        string picked(stack.begin(), stack.end());
        result += stoll(picked);
    }

    return result;
}

void part1() {
    cout << solve(2) << endl;
}

void part2() {
    cout << solve(12) << endl;
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
