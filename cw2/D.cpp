#include <iterator>
#include <algorithm>

template <typename Iter1, typename Iter2>
size_t CountSubsegments(Iter1 first1, Iter1 last1, Iter2 first2, Iter2 last2) {
    size_t ans = 0;
    auto it = std::search(first1, last1, first2, last2);

    while (it != last1) {
        ++ans;
        it = std::search(std::next(it), last1, first2, last2);
    }

    return ans;
}

#include <iostream>
#include <vector>
#include <set>

using namespace std;

int main() {
    std::vector<int> v{1, 1, 2, 10, 1, 0, 1, 2};
    std::set<int> s{1, 2};
    size_t result = CountSubsegments(v.begin(), v.end(), s.cbegin(), s.cend());
    cout << result << "\n";
    return 0;
}
