#include <numeric>

class Rational {
public:
    Rational() : p_(0), q_(1) {}

    Rational(int p) : p_(p), q_(1) {}

    Rational(int p, int q) {
        int d = std::gcd(p, q) * ((q > 0) - (q < 0));
        p_ = p / d;
        q_ = q / d;
    }

    Rational& operator+=(const Rational& other) {
        *this = *this + other;
        return *this;
    }

    Rational operator+(const Rational& other) const {
        return Rational(p_ * other.q_ + other.p_ * q_, q_ * other.q_);
    }

    friend Rational operator+(int x, const Rational& r) {
        return r + x;
    }

    Rational& operator-=(const Rational& other) {
        *this = *this - other;
        return *this;
    }

    Rational operator-(const Rational& other) const {
        return Rational(p_ * other.q_ - other.p_ * q_, q_ * other.q_);
    }

    friend Rational operator-(int x, const Rational& r) {
        return Rational(x) - r;
    }

    Rational& operator*=(const Rational& other) {
        *this = *this * other;
        return *this;
    }

    Rational operator*(const Rational& other) const {
        return Rational(p_ * other.p_, q_ * other.q_);
    }

    friend Rational operator*(int x, const Rational& r) {
        return r * x;
    }

    Rational& operator/=(const Rational& other) {
        *this = *this / other;
        return *this;
    }

    Rational operator/(const Rational& other) const {
        return Rational(p_ * other.q_, q_ * other.p_);
    }

    friend Rational operator/(int x, const Rational& r) {
        return Rational(x) / r;
    }

    int Numerator() const { return p_; }
    int Denominator() const { return q_; }

    bool operator==(const Rational& other) const {
        return p_ == other.p_ && q_ == other.q_;
    }

    bool operator!=(const Rational& other) const {
        return !(*this == other);
    }

    Rational operator+() const {
        return *this;
    }

    Rational operator-() const {
        return Rational(-p_, q_);
    }

    Rational& operator++() {
        *this += 1;
        return *this;
    }

    Rational operator++(int) {
        Rational res(p_, q_);
        *this += 1;
        return res;
    }

    Rational& operator--() {
        *this -= 1;
        return *this;
    }

    Rational operator--(int) {
        Rational res(p_, q_);
        *this -= 1;
        return res;
    }

private:
    int p_;
    int q_;
};


#include <iostream>

using namespace std;

int main() {
    Rational x(2, -4);
    auto y = x++;
    cout << x.Numerator() << "/" << x.Denominator() << "\n";
    cout << y.Numerator() << "/" << y.Denominator() << "\n";
    return 0;
}
