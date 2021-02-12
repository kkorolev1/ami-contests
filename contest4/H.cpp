#include <iostream>

using namespace std;

template <typename InIter, typename OutIter, typename Predicate>
OutIter RemoveCopyIf(InIter first, InIter last, OutIter out, Predicate f) {
    while (first != last) {
        if (f(*first)) {
            *out++ = *first;
        }
        ++first;
    }
    return out;
}

int main() {
    return 0;
}
