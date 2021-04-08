#include <iostream>
#include <string>

using namespace std;

class LoggerGuard {
public:
    LoggerGuard(const string& message = "", ostream& out = std::cout) : mes_(message), os_(out) {
        if (!mes_.empty() && mes_.back() != '\n')
            mes_.push_back('\n');
    }

    ~LoggerGuard() {
        os_ << mes_;
    }

private:
    string mes_;
    ostream& os_;
};

int SomeAnotherFunction() {
    return 42;
}

int SomeSecondFunction() {
    return 42;
}

int FinalFunction() {
    throw 42;
}

int Function() {
    LoggerGuard logger("Function completed\n");

    int value = 1;
    try {
        int value = SomeAnotherFunction();
        if (value == 0) {
            return value;
        }

        value = SomeSecondFunction();
        if (value == 0) {
            return value;
        }

        value = FinalFunction();  // might throw an exception
    } catch (...) {
          // throws the exception further.
    }

    return value;
}

int main() {
    Function();
    return 0;
}
