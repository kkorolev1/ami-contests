#include <iostream>
#include <vector>
#include "c.h"

int main() {
    int n;
    std::cin >> n;
    std::vector<C*> xs(n);

    for (int i = 0; i < n; ++i)
        xs[i] = new C{};

    for (int i = n - 1; i >= 0; --i)
        delete xs[i];

    return 0;
}
