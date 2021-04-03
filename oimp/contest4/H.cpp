template <typename InIter, typename OutIter, typename Predicate>
OutIter RemoveCopyIf(InIter first, InIter last, OutIter out, Predicate f) {
    for (auto it = first; it != last; ++it) {
        if (!f(*it)) {
            *out++ = *it;
        }
    }
    return out;
}

#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> xs = {1, 2, 3, 4, 5, 7};
    vector<int> ys(xs.size());
    auto last = RemoveCopyIf(xs.begin(), xs.end(), ys.begin(), [](int x) {
        return x % 2;
    });

    for (auto it = ys.begin(); it != last; ++it) {
        cout << *it << " ";
    }

    return 0;
}
