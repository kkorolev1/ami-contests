#include <cmath>

class Complex;
double Abs(const Complex& c);

class Complex {
public:
    explicit Complex(double re) : re_(re), im_(0) {}
    Complex(double re, double im) : re_(re), im_(im) {}

    double Re() const { return re_; }
    double Im() const { return im_; }

    Complex operator+(const Complex& other) const {
        return Complex(re_ + other.re_, im_ + other.im_);
    }

    Complex operator+(double re) const {
        return Complex(re_ + re, im_);
    }

    friend Complex operator+(double re, const Complex& c) {
        return c + re;
    }

    Complex operator-(const Complex& other) const {
        return Complex(re_ - other.re_, im_ - other.im_);
    }

    Complex operator-(double re) const {
        return Complex(re_ - re, im_);
    }

    friend Complex operator-(double re, const Complex& c) {
        return Complex(re - c.re_, c.im_);
    }

    Complex operator*(const Complex& other) const {
        return Complex(re_ * other.re_ - im_ * other.im_, re_ * other.im_ + im_ * other.re_);
    }

    Complex operator*(double re) const {
        return Complex(re_ * re, im_ * re);
    }

    friend Complex operator*(double re, const Complex& c) {
        return c * re;
    }

    Complex operator/(const Complex& other) const {
        return Complex(re_ * other.re_ + im_ * other.im_,
                im_ * other.re_ - re_ * other.im_) / (pow(other.re_, 2) + pow(other.im_, 2));
    }

    Complex operator/(double re) const {
        return Complex(re_ / re, im_ / re);
    }

    friend Complex operator/(double re, const Complex& c) {
        return Complex(re, 0) / c;
    }

    Complex operator+() const {
        return *this;
    }

    Complex operator-() const {
        return Complex(-re_, -im_);
    }

    bool operator==(const Complex& other) const {
        return re_ == other.re_ && im_ == other.im_;
    }

    bool operator!=(const Complex& other) const {
        return !(*this == other);
    }

private:
    double re_;
    double im_;
};

double Abs(const Complex& c) {
    return hypot(c.Re(), c.Im());
}

/*
#include <iostream>

using namespace std;

ostream& operator<<(ostream& os, const Complex& c) {
    os << c.Re() << " + " << c.Im() << "j";
    return os;
}

#define check(expr, ans) \
if ((expr) != (ans)) { \
    cout << "Expression: " << #expr << "\n"; \
    cout << "Result: " << (expr) << "\n"; \
    cout << "Answer: " << (ans) << "\n"; \
    return; \
} \

void test() {
    check(Abs(Complex(3, 4)), 5);
    check(Complex(1, 1) * Complex(2, -1), Complex(3, 1));
    check(Complex(4, 3) / Complex(3, -4), Complex(0, 1));
    check(Complex(1, 0) / Complex(0, 1), Complex(0, -1));
    check(-Complex(2, 3), Complex(-2, -3));
    check(1 / Complex(0, 1), Complex(0, -1));
    check(2 * Complex(1, 2), Complex(2, 4));
}

int main() {
    test();
    return 0;
}
*/