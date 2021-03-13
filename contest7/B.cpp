#include <iostream>
#include <exception>
#include <functional>
#include <optional>

using namespace std;

template <typename Result, typename Exception = std::exception>
std::optional<Result> DoWithRetry(std::function<Result()> func, int retryCount, int sleepTime, bool throwLast) {
    for (int curTry = 0; curTry <= retryCount; ++curTry) {
        try {

        } catch ()
    }
}

int main() {
    return 0;
}
