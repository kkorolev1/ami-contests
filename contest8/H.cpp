#include <algorithm>

template <typename T>
class SharedPtr {
    struct Holder {
        T* ptr = nullptr;
        size_t counter = 0;

        Holder() = default;
        Holder(T* ptr) : ptr(ptr), counter(1) {}

        void release() {
            --counter;
            if (counter == 0) {
                delete ptr;
                delete this;
            }
        }
    };

    Holder* holder = nullptr;

public:
    SharedPtr() noexcept = default;

    SharedPtr(T* ptr) : holder(ptr != nullptr ? new Holder(ptr) : nullptr) {}

    SharedPtr(const SharedPtr& other) noexcept : holder(other.holder) {
        ++holder->counter;
    }

    SharedPtr(SharedPtr&& other) noexcept {
        swap(other);
    }

    SharedPtr& operator=(T* ptr) noexcept {
        reset(ptr);
        return *this;
    }

    SharedPtr& operator=(const SharedPtr& other) noexcept {
        if (this != &other) {
            SharedPtr tmp(other);
            swap(tmp);
        }
        return *this;
    }
    SharedPtr& operator=(SharedPtr&& other) noexcept {
        if (this != &other) {
            SharedPtr tmp(std::move(other));
            swap(tmp);
        }
        return *this;
    }

    ~SharedPtr() {
        if (holder) {
            holder->release();
        }
    }

    T& operator*() noexcept {
        return *holder->ptr;
    }

    const T& operator*() const noexcept {
        return *holder->ptr;
    }

    T* operator->() const noexcept {
        return get();
    }

    void reset(T* ptr) noexcept {
        SharedPtr tmp(ptr);
        swap(tmp);
    }

    void swap(SharedPtr& other) noexcept {
        std::swap(holder, other.holder);
    }

    T* get() const noexcept {
        return (holder != nullptr) ? holder->ptr : nullptr;
    }

    explicit operator bool() const noexcept {
        return holder != nullptr;
    }
};


#include <cstddef>
#include <iostream>
#include <memory>
#include <type_traits>

class Test {
private:
    static int counter;
    int id;
public:
    Test() : id(++counter) {
        std::cout << "Test() " << id << "\n";
    }
    Test(const Test& other) : id(++counter) {
        std::cout << "Test(const Test&) " << id << " " << other.id << "\n";
    }
    Test(Test&& other) : id(++counter) {
        std::cout << "Test(Test&&) " << id << " " << other.id << "\n";
    }
    ~Test() {
        std::cout << "~Test() " << id << "\n";
    }
    void foo() const {
        std::cout << "Test::foo() " << id << "\n";
    }
};

int Test::counter = 0;

int main() {
    using T = Test;
    static_assert(sizeof(SharedPtr<T>) == sizeof(T*), "");
    static_assert(std::is_copy_constructible<SharedPtr<T>>::value, "");
    static_assert(std::is_move_constructible<SharedPtr<T>>::value, "");
    static_assert(std::is_constructible<SharedPtr<T>, std::nullptr_t>::value, "");
    static_assert(std::is_constructible<SharedPtr<T>, T*>::value, "");
    static_assert(!std::is_constructible<SharedPtr<T>, std::shared_ptr<T>>::value, "");
    static_assert(!std::is_assignable<SharedPtr<T>, std::shared_ptr<T>>::value, "");
    static_assert(std::is_assignable<SharedPtr<T>, std::nullptr_t>::value, "");
    static_assert(std::is_copy_assignable<SharedPtr<T>>::value, "");
    static_assert(std::is_move_assignable<SharedPtr<T>>::value, "");
    static_assert(std::is_destructible<SharedPtr<T>>::value, "");
    static_assert(!std::is_convertible<SharedPtr<T>, T*>::value, "");
    static_assert(!std::is_convertible<SharedPtr<T>, std::shared_ptr<T>>::value, "");
    static_assert(!std::is_convertible<std::shared_ptr<T>, SharedPtr<T>>::value, "");

    std::cout << "Step 1\n";
    SharedPtr<T> p(new T);

    std::cout << "Step 2\n";
    SharedPtr<T> p2(std::move(p));

    std::cout << "Step 3\n";
    SharedPtr<T> p3;
    std::cout << bool(p3) << std::endl;

    std::cout << "Step 4\n";
    p3 = std::move(p2);

    {
        SharedPtr<int> up1(new int(42));
        SharedPtr<int> up2(new int(17));
        up2 = std::move(up1);
    }

    std::cout << "Step 5\n";
    (*p3).foo();
    p3->foo();
    const auto& cref = p3;
    (*cref).foo();
    cref->foo();

    std::cout << "Step 6\n";
    T * ptr21 = p2.get();
    T * ptr31 = p3.get();
    std::cout << (ptr21 != ptr31) << "\n";
    p2.swap(p3);
    T * ptr22 = p2.get();
    T * ptr32 = p3.get();
    std::cout << (ptr22 == ptr31) << "\n";
    std::cout << (ptr21 == ptr32) << "\n";

    std::cout << "Step 7\n";
    std::cout << bool(p2) << "\n";
    T * np = nullptr;
    p2.reset(np);
    std::cout << bool(p2) << "\n";

    std::cout << "Step 8\n";
    {
        SharedPtr<T> p4(new T);
        p4.reset(new T);
    }

    std::cout << "Step 9\n";
    {
        SharedPtr<T> p1(new T);
        SharedPtr<T> p2(p1);
        SharedPtr<T> p3(nullptr);
        std::cout << bool(p3) << std::endl;
        p3 = p1;
        SharedPtr<T> p4(new T);
        p4 = p2;

        p1->foo();
        p2->foo();
        p3->foo();
        p4->foo();
        std::cout << (p1.get() == p2.get()) << std::endl;
        std::cout << (p2.get() == p3.get()) << std::endl;
        std::cout << (p3.get() == p4.get()) << std::endl;
    }

    std::cout << "Step 10\n";
    {
        SharedPtr<T> p1(new T);
        SharedPtr<T> p2(p1);
        p1.reset(new T);
        p1->foo();
        p2->foo();
        p1 = std::move(p2);
        p1->foo();
        std::cout << bool(p2) << std::endl;
    }

    std::cout << "Step 11\n";
    {
        SharedPtr<T> p1(new T);
        SharedPtr<T> p2(new T);
        SharedPtr<T> p3(p2);
        p2 = std::move(p1);
        p2->foo();
        p3->foo();
    }

    std::cout << "Step 12\n";
    {
        SharedPtr<T> p1(new T);
        SharedPtr<T> p2(new T);
        p2 = std::move(p1);
        p2->foo();
    }

    std::cout << "Step 13\n";
    {
        SharedPtr<T> p1(new T);
        p1 = p1;
        p1->foo();
        p1 = std::move(p1);
        p1->foo();
    }

    std::cout << "End\n";
}
