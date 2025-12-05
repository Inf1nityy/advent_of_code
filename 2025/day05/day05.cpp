#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;

#define ll long long

ll result = 0;
string line;
vector<pair<ll, ll>> intervals;

void part1() {
    while (getline(cin, line)) {
        if (line.empty()) continue;

        size_t delimiter = line.find("-");
        if (delimiter != string::npos) {
            intervals.push_back(pair(
                stoll(line.substr(0, delimiter)), 
                stoll(line.substr(delimiter + 1))
            ));
            continue;
        }

        ll num = stoll(line);
        for (auto interval : intervals) {
            if (num >= interval.first && num <= interval.second) {
                result++;
                break;
            }
        }
    }

    cout << result << endl;
}

void part2() {
    while (getline(cin, line)) {
        if (line.empty()) continue;
        size_t dash = line.find('-');
        if (dash == string::npos) continue;

        ll start = stoll(line.substr(0, dash));
        ll end = stoll(line.substr(dash + 1));
        intervals.push_back({start, end});
    }

    sort(intervals.begin(), intervals.end());

    ll currentStart = -1, currentEnd = -1;
    for (auto &[start, end] : intervals) {
        if (currentEnd < start) {
            if (currentEnd != -1)
                result += currentEnd - currentStart + 1;
            currentStart = start;
            currentEnd = end;
        } else {
            currentEnd = max(currentEnd, end);
        }
    }

    if (currentEnd != -1)
        result += currentEnd - currentStart + 1;

    cout << result << endl;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: ./day05 <1|2>\n";
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
