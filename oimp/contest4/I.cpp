#include <iterator>
#include <algorithm>

template <typename Iter>
Iter Unique(Iter first, Iter last) {
    if (std::distance(first, last) <= 1) {
        return last;
    }

    auto new_last = last;
    auto it = ++first;

    while (it != new_last) {
        if (*it == *std::prev(it)) {
            std::rotate(it, std::next(it), new_last);
            --new_last;
        } else {
            ++it;
        }
    }

    return new_last;
}

#include <iostream>
#include <vector>

using namespace std;

vector<int> xs = {5, 8, 8, 8, 8, 8, 9};

int main() {
    auto last = Unique(xs.begin(), xs.end());

    for (auto it = xs.begin(); it != last; ++it) {
         cout << *it << " ";
    }

    return 0;
}
