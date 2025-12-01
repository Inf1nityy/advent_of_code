#include <bits/stdc++.h>
#include <string>
using namespace std;

int dial = 50;
int result = 0;
string line;

void part1() {
    while (getline(cin, line)) {
        int rotation = stoi(line.substr(1));
        dial = ((line[0] == 'R') ? (dial + rotation) : (dial - rotation)) % 100;
        if (dial == 0) result++;
    }

    cout << result << endl;
}

void part2() {
    while (getline(cin, line)) {
        int rotation = stoi(line.substr(1));
        if (line[0] == 'L') rotation = -rotation;

        int boundToAdd = (dial == 0) ? 0 : 1;
        int newPos = dial + (rotation % 100);

        if (newPos > 99) {
            newPos -= 100;
            result += boundToAdd;
        } else if (newPos < 0) {
            newPos += 100;
            result += boundToAdd;
        } else if (newPos == 0) {
            result += boundToAdd;
        }

        result += abs(rotation / 100);
        dial = newPos;
    }

    cout << result << endl;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: ./day01 <1|2>\n";
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
