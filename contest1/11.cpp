#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    freopen("input.txt", "r", stdin);
    vector<string> lines;
    lines.reserve(1000);

    string line;

    while (getline(cin, line)) {
        lines.push_back(move(line));
    }

    sort(lines.begin(), lines.end(), greater<string>{});

    for (const auto& s : lines) {
        cout << s << "\n";
    }

    return 0;
}

