template <typename InIter1, typename InIter2, typename OutIter>
OutIter SetDifference(InIter1 first1, InIter1 last1, InIter2 first2, InIter2 last2, OutIter out) {
    while (first1 != last1) {
        while (first2 != last2 && *first2 < *first1) {
            ++first2;
        }

        if ((first2 == last2) || (first2 != last2 && *first2 != *first1)) {
            *out++ = *first1;
        }

        if (first2 != last2 && *first2 == *first1) {
            ++first2;
        }

        ++first1;
    }
    return out;
}

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    vector<int> xs = {1, 1, 3, 3, 3, 6, 7};
    vector<int> ys = {-100, -50, 1, 1, 3, 3, 6, 7};
    vector<int> zs1, zs2;
    SetDifference(xs.begin(), xs.end(), ys.begin(), ys.end(), back_inserter(zs1));
    set_difference(xs.begin(), xs.end(), ys.begin(), ys.end(), back_inserter(zs2));

    if (equal(zs1.begin(), zs1.end(), zs2.begin())) {
        cout << "OK\n";

        for (int x : zs1) {
            cout << x << " ";
        }

    } else {
        cout << "WA";
    }

    return 0;
}
