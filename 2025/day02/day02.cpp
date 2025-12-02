#include <bits/stdc++.h>
using namespace std;

bool repeats_twice(long long num) {
    string s = to_string(num);
    if (s.size() % 2 != 0) return false;
    size_t half = s.size() / 2;
    return s.compare(0, half, s, half, half) == 0;
}

void part1() {
    string input;
    getline(cin, input);
    stringstream ss(input);
    string range;

    long long total = 0;

    while (getline(ss, range, ',')) {
        size_t dash = range.find('-');
        long long low  = stoll(range.substr(0, dash));
        long long high = stoll(range.substr(dash + 1));

        for (long long i = low; i <= high; i++) {
            if (repeats_twice(i)) {
                total += i;
            }
        }
    }

    cout << total << "\n";
}

bool repeats_at_least_twice(long long num) {
    string s = to_string(num);
    int n = s.length();
    for (int len = 1; len <= n/2; len++) {
        if (n % len != 0) continue;
        string prefix = s.substr(0, len);
        string repeated;
        int reps = n / len;
        for (int r = 0; r < reps; r++) repeated += prefix;
        if (repeated == s) return true;
    }
    return false;
}

void part2() {
    string input;
    getline(cin, input);
    stringstream ss(input);
    string range;

    long long total = 0;

    while (getline(ss, range, ',')) {
        size_t dash = range.find('-');
        long long low  = stoll(range.substr(0, dash));
        long long high = stoll(range.substr(dash + 1));

        for (long long i = low; i <= high; i++) {
            if (repeats_at_least_twice(i)) {
                total += i;
            }
        }
    }

    cout << total << "\n";
}

// ---------------- Main ----------------
int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: ./day02 <1|2>\n";
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

