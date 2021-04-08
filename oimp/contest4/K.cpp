#include <iterator>

template <typename InIter, typename OutIter>
OutIter ReverseCopy(InIter first, InIter last, OutIter out) {
    for (auto it = last; it != first; --it) {
        *out++ = *std::prev(it);
    }

    return out;
}

#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> xs = {};
    vector<int> ys(xs.size());
    auto last = ReverseCopy(xs.begin(), xs.end(), ys.begin());

    for (auto it = ys.begin(); it != last; ++it) {
        cout << *it << " ";
    }

    return 0;
}
