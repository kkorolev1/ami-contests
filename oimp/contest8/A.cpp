#include <cstddef>
#include <utility>

template <typename T>
class UniquePtr {
public:
    UniquePtr() noexcept : t(nullptr) {}

    UniquePtr(T* ptr) noexcept : t(ptr) {}

    UniquePtr(UniquePtr&& other) noexcept : t(nullptr) {
        swap(other);
    }

    UniquePtr& operator=(std::nullptr_t) noexcept {
        reset(nullptr);
        return *this;
    }

    UniquePtr& operator=(UniquePtr&& other) noexcept {
        if (this != &other) {
            reset(other.release());
        }
        return *this;
    }

    ~UniquePtr() {
        delete t;
    }

    T& operator*() const {
        return *t;
    }

    T* operator->() const noexcept {
        return t;
    }

    T* release() noexcept {
        T* ptr = nullptr;
        std::swap(t, ptr);
        return ptr;
    }

    void reset(T* ptr) noexcept {
        T* tCpy = t;
        t = ptr;
        if (tCpy != nullptr) {
            delete tCpy;
        }
    }

    void swap(UniquePtr& other) noexcept {
        std::swap(t, other.t);
    }

    T* get() const noexcept {
        return t;
    }

    explicit operator bool() const noexcept {
        return t != nullptr;
    }

    UniquePtr(const UniquePtr&) = delete;

    UniquePtr& operator=(const UniquePtr& other) = delete;

private:
    T* t;
};

#include <iostream>
using namespace std;

struct Point {
    int x;
    int y;
};

ostream& operator<<(ostream& os, Point p) {
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}

int main() {
    UniquePtr<Point> p1;
    p1.reset(new Point{1, -1});
    cout << *p1 << "\n";
    auto p2 = move(p1);
    cout << p2->x << " " << p2->y << "\n";
    auto ptr = p2.release();
    delete ptr;

    UniquePtr<Point> p3(new Point{42, -42});
    p3 = nullptr;

    if (!p3) { cout << "OK\n"; }

    UniquePtr<Point> p4(new Point{42, -42});
    UniquePtr<Point> p5(move(p4));

    cout << p4.get() << "\n";
    cout << *p5 << "\n";

    UniquePtr<Point> p6;

    return 0;
}
