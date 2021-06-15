#include <iostream>
#include <vector>
#include <set>
using namespace std;

set<int> not_visited;
vector<int> ans;

void rec(int depth, int n) {
    if (depth == n) {
        for (int x : ans) {
            cout << x;
        }
        cout << "\n";
        return;
    }

    for (auto it = not_visited.begin(); it != not_visited.end(); ++it) {
        int x = *it;
        ans.push_back(x);
        it = not_visited.erase(it);
        rec(depth+1, n);
        ans.pop_back();
        it = not_visited.insert(x).first;
    }
}

void print_permutations(size_t n) {
    rec(0, n);
}

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i)
        not_visited.insert(i);
    print_permutations(n);
    return 0;
}
