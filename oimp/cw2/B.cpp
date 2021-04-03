#include <cstdint>
#include <set>
#include <iterator>

void RemoveEvenElements(std::set<int64_t>& s) {
    if (s.empty()) {
        return;
    }

    auto it = std::next(s.begin());

    while (it != s.end()) {
        auto prev = std::prev(it++);
        if ((*prev % 2) == 0) {
            s.erase(prev);
        }
    }

    auto prev = std::prev(it);

    if ((*prev % 2) == 0) {
        s.erase(prev);
    }
}

#include <iostream>

using namespace std;

int main() {
    set<int64_t> xs = {2, 1};
    RemoveEvenElements(xs);

    for (auto x : xs) {
        cout << x << " ";
    }

    return 0;
}
