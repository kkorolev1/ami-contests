template<typename Iterator, typename T, typename BinaryOp>
T Reduce(Iterator first, Iterator last, T init, BinaryOp op) {
    T result = init;

    for (auto it = first; it != last; ++it) {
        result = op(result, *it);
    }

    return result;
}

#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> xs = {1, 2, 3, 4};
    auto ans = Reduce(xs.begin(), xs.end(), 0, [](int init, int x) {
        return init + x;
    });

    cout << ans << "\n";

    return 0;
}
