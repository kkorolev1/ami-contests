#include <cstddef>
#include <utility>
#include <memory>
#include <tuple>

template <typename T, typename Deleter = std::default_delete<T>>
class UniquePtr {
public:
    UniquePtr() noexcept : data(std::make_tuple(nullptr, Deleter())) {}

    UniquePtr(T* ptr) noexcept : data(std::make_tuple(ptr, Deleter())) {}

    UniquePtr(T* ptr, const Deleter& deleter) noexcept : data(std::make_tuple(ptr, deleter)) {}

    UniquePtr(UniquePtr&& other) noexcept :
        data(std::make_tuple(other.release(), other.get_deleter())) {}

    UniquePtr& operator=(std::nullptr_t) noexcept {
        reset();
        return *this;
    }

    UniquePtr& operator=(UniquePtr&& other) noexcept {
        if (this != &other) {
            reset(other.release());
            get_deleter() = other.get_deleter();
        }
        return *this;
    }

    ~UniquePtr() {
        if (get())
            get_deleter()(get());
    }

    T& operator*() const {
        return *get();
    }

    T* operator->() const noexcept {
        return get();
    }

    T* release() noexcept {
        T* ptr = get();
        std::get<0>(data) = nullptr;
        return ptr;
    }

    void reset(T* ptr = nullptr) noexcept {
        T* tCpy = get();
        std::get<0>(data) = ptr;
        if (tCpy != nullptr) {
            get_deleter()(tCpy);
        }
    }

    void swap(UniquePtr& other) noexcept {
        auto& ptr = std::get<0>(data);
        auto& otherPtr = std::get<0>(other.data);
        std::swap(ptr, otherPtr);
    }

    T* get() const noexcept {
        return std::get<0>(data);
    }

    explicit operator bool() const noexcept {
        return get() != nullptr;
    }

    UniquePtr(const UniquePtr&) = delete;

    UniquePtr& operator=(const UniquePtr& other) = delete;

    Deleter& get_deleter() noexcept {
        return std::get<1>(data);
    }

    const Deleter& get_deleter() const noexcept {
        return std::get<1>(data);
    }

private:
    std::tuple<T*, Deleter> data;
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
    auto deleter = [](Point* p) {
        cout << "[deleter] " << p << "\n";
        delete p;
    };

    using SmartPtr = UniquePtr<Point, decltype(deleter)>;

    SmartPtr p1(new Point{-12, 5}, deleter);
    cout << *p1 << "\n";

    auto p2 = move(p1);
    p2.reset(new Point{4, 8});
    cout << p2->x << " " << p2->y << "\n";

    auto ptr = p2.release();
    cout << ptr->x << " " << ptr->y << "\n";
    delete ptr;

    SmartPtr p3(new Point{1000, 1000}, deleter);
    SmartPtr p4(new Point{2000, 2000}, deleter);
    p3.swap(p4);
    cout << *p4 << "\n";

    /*unique_ptr<Point, decltype(deleter)> ptr1(new Point{-12, 5}, deleter);
    auto ptr2 = move(ptr1);
    cout << *ptr2 << "\n";*/

    return 0;
}
