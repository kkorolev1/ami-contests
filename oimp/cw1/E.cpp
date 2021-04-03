#include <iostream>

using namespace std;

#include <vector>

template <typename T>
void Duplicate(std::vector<T>& v) {
    const auto size = v.size();
    v.reserve(2 * size);
    for (size_t i = 0; i < size; ++i)
        v.push_back(v[i]);
}

int main() {
    vector<int> xs = {1, 2, 3, 4};
    Duplicate(xs);

    for (int x : xs)
        cout << x << " ";

    return 0;
}
