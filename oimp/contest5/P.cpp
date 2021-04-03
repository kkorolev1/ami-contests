#include <string>
#include <iostream>
#include <string_view>
#include <chrono>

class TimerGuard {
public:
    using TimePoint = decltype(std::chrono::high_resolution_clock::now());

    TimerGuard(std::string_view message = "", std::ostream& out = std::cout) :
        mes_(message), os_(out) {
        start_ = std::chrono::high_resolution_clock::now();
    }

    ~TimerGuard() {
        std::chrono::duration<double> diff = std::chrono::high_resolution_clock::now() - start_;
        os_ << mes_ << " " << diff.count() << "\n";
    }

private:
    std::string mes_;
    std::ostream& os_;
    TimePoint start_;
};

#include <vector>
#include <algorithm>
#include <random>
using namespace std;

/*void FirstLongFunction() {
    vector<int> xs(10e6);
    random_device rd;
    mt19937 gen(rd());
    shuffle(xs.begin(), xs.end(), gen);
}*/



/*int main() {
    {
        TimerGuard timer("FirstLongFunction elapsed:", std::cerr);
        FirstLongFunction();
    }

    return 0;
} */
