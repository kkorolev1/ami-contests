#include <iostream>
#include <map>
#include <vector>

using namespace std;

int main() {
    freopen("input.txt", "r", stdin);
    int n;
    cin >> n;

    map<int, string> cws;
    int top = 0, bottom = 0;

    for (int i = 0; i < n; ++i) {
        string surname, op;
        cin >> surname >> op;

        if (op == "top") {
            --top;
            cws.emplace(top, surname);
        } else {
            ++bottom;
            cws.emplace(bottom, surname);
        }
    }

    vector<pair<int, string>> cws_pairs(cws.begin(), cws.end());

    int m;
    cin >> m;

    for (int i = 0; i < m; ++i) {
        int x;
        cin >> x;
        cout << cws_pairs[x - 1].second << "\n";
    }

    return 0;
}
