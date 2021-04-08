#include <iostream>
#include <unordered_map>
#include <forward_list>
using namespace std;

int main() {
    // freopen("input.txt", "r", stdin);
    int n;
    cin >> n;

    forward_list<int> sportsmen;
    using Iter = typename forward_list<int>::iterator;
    unordered_map<int, Iter> lookup;

    for (int i = 0; i < n; ++i) {
        int pos, prev_pos;
        cin >> pos >> prev_pos;
        auto it = lookup.find(prev_pos);

        if (it == lookup.end()) {
            sportsmen.push_front(pos);
            lookup[pos] = sportsmen.begin();
        } else {
            auto inserted_it = sportsmen.insert_after(it->second, pos);
            lookup[pos] = inserted_it;
        }
    }

    for (int s : sportsmen) {
        cout << s << "\n";
    }

    return 0;
}
