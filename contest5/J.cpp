#include <deque>

template <typename T, typename Container = std::deque<T>>
class Queue {
public:
    Queue() = default;

    const T& front() const { return c_.front(); }
    T& front() { return c_.front(); }

    void pop() {
        c_.pop_front();
    }

    void push(const T& value) {
        c_.push_back(value);
    }

    size_t size() const { return c_.size(); }
    bool empty() const { return c_.empty(); }

    bool operator==(const Queue& other) const {
        return c_ == other.c_;
    }

    bool operator!=(const Queue& other) const {
        return c_ != other.c_;
    }

private:
    Container c_;
};

#include <iostream>

using namespace std;

int main() {
    Queue<int> q;
    q.push(1);
    q.push(2);
    q.pop();
    q.push(3);

    while (!q.empty()) {
        std::cout << q.front() << " ";
        q.pop();
    }

    return 0;
}
