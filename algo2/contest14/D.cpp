#include <iostream>
#include <unordered_map>
using namespace std;

struct Counter {
    unordered_map<char, int> mp;
    int max_freq;

    Counter(int max_freq) : max_freq(max_freq) {}

    bool is_ok(char c) {
        return mp[c] < max_freq;
    }

    void add(char c) {
        ++mp[c];
    }

    void remove(char c) {
        --mp[c];

        if (!mp[c]) {
            mp.erase(c);
        }
    }
};

int main() {
    ios::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    cin >> n >> k;

    string s;
    cin >> s;

    Counter c(k);
    int max_len = 0;
    int first_idx = 0;

    for (int l = 0, r = 0; l < n; ++l) {
        while (r < n && c.is_ok(s[r])) {
            c.add(s[r++]);
        }
        if (r - l > max_len) {
            max_len = r - l;
            first_idx = l;
        }
        c.remove(s[l]);
    }

    cout << max_len << " " << first_idx+1 << "\n";

    return 0;
}
