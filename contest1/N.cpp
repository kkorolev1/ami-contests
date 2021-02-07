#include <iostream>
#include <unordered_set>
#include <string>
#include <algorithm>
#include <string_view>
#include <vector>

using namespace std;

using Segment = pair<size_t, size_t>;

string to_lower(const string& str) {
    string res(str.size(), 0);
    transform(str.begin(), str.end(), res.begin(), [](char c) { return tolower(c); });
    return res;
}

void transform_word(const unordered_set<string>& dict, const string& str) {
    size_t len = str.size();

    if (len == 0) {
        return;
    }

    vector<Segment> segments;

    for (size_t i = 0; i < len; ++i) {
        for (size_t j = len; j > i; --j) {
            auto substr = str.substr(i, j - i);

            if (dict.find(to_lower(substr)) != dict.end()) {
                if (!segments.empty() && i <= segments.back().second) {
                    auto& to = segments.back().second;
                    if (j > to) {
                        to = j;
                    }
                } else {
                    segments.emplace_back(i, j);
                }
                break;
            }
        }
    }

    if (segments.empty()) {
        cout << str;
        return;
    }

    if (segments.front().first > 0) {
        cout << str.substr(0, segments.front().first);
    }

    for (size_t i = 0; i < segments.size(); ++i) {
        auto [from, to] = segments[i];
        if (i > 0) {
            auto [prev_from, prev_to] = segments[i - 1];
            cout << str.substr(prev_to, from - prev_to);
        }
        cout << string(to - from, '*');
    }

    if (segments.back().second < len) {
        cout << str.substr(segments.back().second);
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n;
    cin >> n;

    unordered_set<string> dict;

    for (int i = 0; i < n; ++i) {
        string word;
        cin >> word;
        dict.insert(to_lower(word));
    }

    cin.ignore();
    cin >> noskipws;
    char c;

    string word;

    while (cin >> c) {
        if (!isalpha(c)) {
            transform_word(dict, word);
            cout << c;
            word = "";
            continue;
        }
        word += c;
    }

    transform_word(dict, word);

    return 0;
}
