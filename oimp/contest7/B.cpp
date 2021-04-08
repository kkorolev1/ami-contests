#include <iostream>
#include <exception>
#include <functional>
#include <optional>

using namespace std;

template <typename Result, typename Exception = std::exception>
std::optional<Result> DoWithRetry(
        std::function<Result()> func, int retryCount, int sleepTime, bool throwLast) {
    for (int curTry = 0; curTry <= retryCount; ++curTry) {
        try {
            return func();
        } catch (const Exception& exc) {
            if (curTry < retryCount) {
                Sleep(sleepTime);
            } else if (throwLast) {
                throw exc;
            }
        }
    }
    return {};
}

#include <zconf.h>

void Sleep(int sleepTime) {
    sleep(1000 * sleepTime);
}

int main() {
    auto res = DoWithRetry<int>([]() {
        return 42;
    }, 3, 1, false);

    if (res) {
        cout << *res << "\n";
    } else {
        cout << "no val\n";
    }

    return 0;
}
