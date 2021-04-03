#include <algorithm>
#include <vector>
#include <iterator>

#include <iostream>
template <typename T>
void print_results(T first, T last) {
    while (first != last) {
        std::cout << *first++ << " ";
    }
    std::cout << "\n";
}

template <typename T>
void process(const std::vector<T>& data) {
    std::vector<T> filtered;
    std::copy_if(
            data.cbegin(),
            data.cend(),
            std::back_inserter(filtered),
            [](const T& x) { return x > 0; });

    print_results(filtered.begin(), filtered.end());
}

#include <iostream>

using namespace std;

int main() {
    vector<int> xs = {-100, -50, 50, 100};
    process(xs);
    return 0;
}
