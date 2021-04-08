#include <algorithm>
#include <vector>

void delete_zeroes(std::vector<int>& numbers) {
    numbers.erase(
            std::remove(numbers.begin(), numbers.end(), 0),
            numbers.end());
}

#include <iostream>

using namespace std;

int main() {
    vector<int> xs = {0, 1, 0, 0, 2, 3, 4, 0, 0, 5, 0};
    delete_zeroes(xs);

    for (int x : xs) {
        cout << x << " ";
    }

    return 0;
}
