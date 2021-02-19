#include "c.h"

int main() {
    C c1, c2;
    c1 = c2;
    c1 = std::move(c2);
    return 0;
}
