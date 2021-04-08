#include <iostream>
#include <memory>

class A {
public:
    A(int x) {
        std::cout << "Constructor(int): " << x << "\n";
    }
    A(const A&) {
        std::cout << "Copy constructor\n";
    }
    virtual ~A() {
        std::cout << "Destructor\n";
    }
    virtual void foo() const {
        std::cout << "A::foo()\n";
    }
};

class B : public A {
public:
    B() : A(42), a(17) {}

    A a;
};

int main() {
    std::unique_ptr<A> ptr(new B);
    ptr->foo();
}
