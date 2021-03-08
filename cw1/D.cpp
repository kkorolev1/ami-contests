#include <iostream>
#include <forward_list>

#include <algorithm>
#include <iterator>
using namespace std;

template <typename Iterator>
bool IsUnique(Iterator begin, Iterator end) {
    size_t dt = distance(begin, end);

    while (dt > 1) {
        auto last = next(begin, dt);
        for (auto jt = begin; jt != last; ++jt) {
            if (next(jt) != last && *jt > *next(jt))
                iter_swap(jt, next(jt));
        }
        --dt;
    }
    return unique(begin, end) == end;
}

int main() {
    forward_list<int> xs = {4, 9, 8, 7, 6, 5, 4};
    cout << IsUnique(xs.begin(), xs.end()) << "\n";

    for (int x : xs)
        cout << x << " ";

    return 0;
}
