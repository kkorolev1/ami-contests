#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    // freopen("input1.txt", "r", stdin);
    size_t m, n;
    cin >> m >> n;

    string word;
    unordered_map<string, int> freq;

    while (cin >> word) {
        if (word.size() >= n) {
            for (size_t i = 0; i < word.size() - n + 1; ++i) {
                ++freq[word.substr(i, n)];
            }
        }
    }

    using Pair = pair<string, int>;
    vector<Pair> freq_v(freq.begin(), freq.end());
    sort(freq_v.begin(), freq_v.end(), [](const Pair& lhs, const Pair& rhs) {
        if (lhs.second != rhs.second) {
            return lhs.second > rhs.second;
        }
        return lhs.first < rhs.first;
    });

    for (auto& p : freq_v) {
        cout << p.first << " - " << p.second << "\n";
    }

    return 0;
}
