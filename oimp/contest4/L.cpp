template <typename InIter, typename OutIter, typename Predicate, typename Action>
OutIter TransformIf(InIter first, InIter last, OutIter out, Predicate condition, Action f) {
    for (auto it = first; it != last; ++it) {
        if (condition(*it)) {
            *out++ = f(*it);
        }
    }
    return out;
}

#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> xs = {1, 2, 3, 4, 5, 6, 7, 8};
    vector<int> ys(xs.size());
    auto last = TransformIf(xs.begin(), xs.end(), ys.begin(),
            [](int x) { return (x % 2) == 0; }, [](int x){ return x * x; });

    for (auto it = ys.begin(); it != last; ++it) {
        cout << *it << " ";
    }

    return 0;
}
