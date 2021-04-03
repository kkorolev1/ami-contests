#include <iostream>
#include <string>
#include <vector>
#include <set>
using namespace std;

int main() {
    // freopen("input.txt", "r", stdin);
    int n;
    cin >> n;

    const size_t MAX_SIZE = 1000;
    vector<set<string>> pages(MAX_SIZE);

    for (int i = 0; i < n; ++i) {
        string word;
        cin >> word;
        int page_num;
        cin >> page_num;
        auto& s = pages[page_num - 1];
        s.insert(word);
    }

    for (size_t i = 0; i < MAX_SIZE; ++i) {
        auto& s = pages[i];
        if (!s.empty()) {
            cout << (i + 1);
            for (auto& word : s) {
                cout << " " << word;
            }
            cout << "\n";
        }
    }

    return 0;
}
