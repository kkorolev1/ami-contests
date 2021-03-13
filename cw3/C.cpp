#include <iostream>
#include <cstddef>
#include <vector>
#include <stdexcept>

using namespace std;

template <typename T>
class Deque {
private:
    std::vector<T> head, tail;

public:
    bool Empty() const {
        return head.empty() && tail.empty();
    }

    size_t Size() const {
        return head.size() + tail.size();
    }

    void Clear() {
        head.clear();
        tail.clear();
    }

    const T& operator[] (size_t i) const {
        if (i < head.size())
            return head[head.size() - i - 1];
        return tail[i - head.size()];
    }

    T& operator[] (size_t i) {
        if (i < head.size())
            return head[head.size() - i - 1];
        return tail[i - head.size()];
    }

    const T& At(size_t i) const {
        if (i >= Size())
            throw out_of_range("Incorrect index");
        return this->operator[](i);
    }

    T& At(size_t i) {
        if (i >= Size())
            throw out_of_range("Incorrect index");
        return this->operator[](i);
    }

    const T& Front() const {
        if (!head.empty())
            return head.back();
        return tail.front();
    }

    T& Front() {
        if (!head.empty())
            return head.back();
        return tail.front();
    }

    const T& Back() const {
        if (!tail.empty())
            return tail.back();
        return head.front();
    }

    T& Back() {
        if (!tail.empty())
            return tail.back();
        return head.front();
    }

    void PushFront(const T& elem) {
        head.push_back(elem);
    }

    void PushBack(const T& elem) {
        tail.push_back(elem);
    }
};

int main() {
    try {
        Deque<int> d;
        /*d.PushBack(3);
        d.PushFront(2);
        cout << d.At(0) << ", " << d.At(1) << "\n";
        cout << "size=" << d.Size() << "\n";
        d.PushBack(4);
        d.PushBack(5);
        d.PushFront(1);
        d.PushFront(0);
        cout << "size=" << d.Size() << "\n";
        cout << d.At(0) << ", " << d.At(1) << ", " << d.At(2) << ", " << d.At(3) << ", " << d.At(4) << ", " << d.At(5) << "\n";
        d.Clear();
        cout << "size=" << d.Size() << "\n"; */
        d.PushFront(1);
        d.PushFront(2);
        d.PushFront(3);
        d.PushFront(4);
        cout << d.Front() << " " << d.Back() << "\n";
    } catch (exception& ex) {
        cout << ex.what() << "\n";
    }

    return 0;
}
