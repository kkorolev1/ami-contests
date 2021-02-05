#include <algorithm>
#include <vector>

std::vector<int> Range(const std::vector<int>& v, size_t start, size_t end, size_t step = 1) {
    std::vector<int> res;
    end = std::min(v.size(), end);

    while (start < end) {
        res.push_back(v[start]);
        if (start + step < start) {
            break;
        }
        start += step;
    }

    return res;
}


#include <iostream>

int main() {
    std::vector<int> v = {1, 2, 3, 4, 5};
    auto ans = Range(v, 0, 5, 1000000000);

    for (int x : ans) {
        std::cout << x << " ";
    }

    return 0;
}