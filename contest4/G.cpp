#include <iostream>

using namespace std;

template <typename It, typename Pred>
bool AnyOf(It first, It last, Pred f) {
    while (first != last) {
        if (f(*first++))
            return true;
    }
    return false;
}


#include <vector>
template <typename Iter, typename Pred>
bool test(Iter first, Iter last, Pred f, bool ans) {
    return AnyOf(first, last, f) == ans;
}

int main() {
    vector<int> nums = {1, 2, 3, 4, 5};
    cout << (test(nums.begin(), nums.end(), [](int x){ return x > 10; }, false) ? "OK" : "WA") << "\n";
    return 0;
}
