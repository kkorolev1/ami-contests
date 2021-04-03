#include <iterator>

template <typename It, typename OutputIt>
OutputIt SidewaysMerge(It first1, It last1, It first2, It last2, OutputIt out) {
    while (first1 != last1 && first2 != last2) {
        auto last2_prev = std::prev(last2);

        if (*first1 < *last2_prev) {
            *out++ = *first1++;
        } else {
            *out++ = *last2_prev;
            --last2;
        }
    }

    while (first1 != last1) {
        *out++ = *first1++;
    }

    while (first2 != last2) {
        *out++ = *std::prev(last2);
        --last2;
    }

    return out;
}

#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> xs = {1, 2, 3};
    vector<int> ys = {8, 7};
    vector<int> zs;
    SidewaysMerge(xs.begin(), xs.end(), ys.begin(), ys.end(), back_inserter(zs));

    for (auto it = zs.begin(); it != zs.end(); ++it) {
        cout << *it << " ";
    }

    return 0;
}
