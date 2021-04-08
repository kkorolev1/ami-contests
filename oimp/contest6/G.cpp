#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

template <typename T>
class Polynomial {
public:
    Polynomial(const vector<T>& coeffs) :
        Polynomial(coeffs.begin(), coeffs.end()) {}

    Polynomial(const T& value = T()) : Polynomial(vector<T>(1, value)) {}

    template <typename Iter>
    Polynomial(Iter first, Iter last) : coeffs_(first, last) {
        removeZeroes();
    }

    bool operator==(const Polynomial& other) const {
        return coeffs_ == other.coeffs_;
    }

    bool operator!=(const Polynomial& other) const {
        return !(*this == other);
    }

    Polynomial& operator+=(const Polynomial& other) {
        auto minDeg = min(coeffs_.size(), other.coeffs_.size());
        for (size_t i = 0; i < minDeg; ++i) {
            coeffs_[i] += other.coeffs_[i];
        }
        if (coeffs_.size() < other.coeffs_.size()) {
            coeffs_.resize(other.coeffs_.size());
            for (size_t i = minDeg; i < other.coeffs_.size(); ++i)
                coeffs_[i] = other.coeffs_[i];
        }
        removeZeroes();
        return *this;
    }

    Polynomial& operator-=(const Polynomial& other) {
        auto minDeg = min(coeffs_.size(), other.coeffs_.size());
        for (size_t i = 0; i < minDeg; ++i) {
            coeffs_[i] -= other.coeffs_[i];
        }
        if (coeffs_.size() < other.coeffs_.size()) {
            coeffs_.resize(other.coeffs_.size());
            for (size_t i = minDeg; i < other.coeffs_.size(); ++i)
                coeffs_[i] = -other.coeffs_[i];
        }
        removeZeroes();
        return *this;
    }


    Polynomial& operator*=(const Polynomial& other) {
        vector<T> coeffs(Degree() + other.Degree() + 1, ZERO);
        for (size_t i = 0; i < coeffs_.size(); ++i) {
            for (size_t j = 0; j < other.coeffs_.size(); ++j) {
                coeffs[i + j] += coeffs_[i] * other.coeffs_[j];
            }
        }
        coeffs_.swap(coeffs);
        removeZeroes();
        return *this;
    }

    friend Polynomial operator+(Polynomial lhs, const Polynomial& rhs) {
        lhs += rhs;
        return lhs;
    }

    friend Polynomial operator-(Polynomial lhs, const Polynomial& rhs) {
        lhs -= rhs;
        return lhs;
    }


    friend Polynomial operator*(Polynomial lhs, const Polynomial& rhs) {
        lhs *= rhs;
        return lhs;
    }

    const T& operator[](int degree) const {
        if (degree > Degree())
            return ZERO;
        return coeffs_[degree];
    }

    int Degree() const {
        if (coeffs_.empty())
            return -1;
        return coeffs_.size() - 1;
    }


    T operator()(const T& arg) const {
        T res(0);

        for (size_t i = coeffs_.size(); i > 0; --i) {
            res = coeffs_[i - 1] + res * arg;
        }

        return res;
    }


    friend ostream& operator<<(ostream& os, const Polynomial& poly) {
        if (poly.coeffs_.empty()) {
            os << ZERO;
            return os;
        }

        for (size_t i = poly.coeffs_.size(); i > 0; --i) {
            auto val = poly.coeffs_[i - 1];
            if (val != ZERO) {
                if (val > ZERO) {
                    if (i != poly.coeffs_.size())
                        os << "+";
                    if (i == 1 || val != T(1))
                        os << val;
                } else {
                    if (i == 1 || val != T(-1))
                        os << val;
                    else
                        os << "-";
                }


                if (i > 1 && (val != T(1) && val != T(-1)))
                    os << "*";

                if (i > 1)
                    os << "x";

                if (i > 2)
                    os << "^" << (i - 1);
            }
        }

        return os;
    }

    using Iterator = typename vector<T>::const_iterator;

    Iterator begin() const { return coeffs_.begin(); }
    Iterator end() const { return coeffs_.end(); }

    friend Polynomial operator&(const Polynomial& lhs, const Polynomial& rhs) {
        if (lhs.coeffs_.empty())
            return Polynomial();

        Polynomial res(lhs.coeffs_[0]);
        auto powers_of_rhs = rhs;

        for (size_t i = 1; i < lhs.coeffs_.size(); ++i) {
            res += lhs.coeffs_[i] * powers_of_rhs;
            powers_of_rhs *= rhs;
        }

        return res;
    }

    friend Polynomial operator/(const Polynomial& lhs, const Polynomial& rhs) {
        return longDivision(lhs, rhs).first;
    }

    friend Polynomial operator%(const Polynomial& lhs, const Polynomial& rhs) {
        return longDivision(lhs, rhs).second;
    }

    friend Polynomial operator,(const Polynomial& lhs, const Polynomial& rhs) {
        if (lhs.Degree() < rhs.Degree())
            return (rhs, lhs);

        auto p = lhs;
        auto q = rhs;
        Polynomial zero;

        while (q != zero) {
            auto r = p % q;
            p = move(q);
            q = move(r);
        }

        return p / p.coeffs_.back();
    }

private:
    static pair<Polynomial, Polynomial> longDivision(const Polynomial& lhs, const Polynomial& rhs) {
        if (lhs.coeffs_.empty())
            return {lhs, lhs};

        if (lhs.Degree() < rhs.Degree())
            return {Polynomial(), lhs};

        auto cur_poly = lhs;
        Polynomial q;

        while (cur_poly.Degree() >= rhs.Degree()) {
            const auto& d = cur_poly.coeffs_.back() /
                            rhs.coeffs_.back();

            auto deg = cur_poly.Degree() - rhs.Degree();
            vector<T> coeffs(deg + 1, ZERO);
            coeffs[deg] = d;
            Polynomial tmp(coeffs);

            q += tmp;
            cur_poly -= tmp * rhs;
        }

        return {q, cur_poly};
    }

    static bool isNotZero(const T& val) {
        return val != ZERO;
    }

    void removeZeroes() {
        auto rit = std::find_if(coeffs_.rbegin(), coeffs_.rend(), isNotZero);
        coeffs_.erase(rit.base(), coeffs_.end());
    }

private:
    static T ZERO;
    vector<T> coeffs_;
};

template <typename T>
T Polynomial<T>::ZERO = T(0);


#define check(expr, ans) \
if ((expr) != (ans)) { \
    cout << "Expression: " << #expr << "\n"; \
    cout << "Result: " << (expr) << "\n"; \
    cout << "Answer: " << (ans) << "\n"; \
    return; \
} \

void test() {
    check(Polynomial<int>(vector<int>{0, 0, 0, 0}), Polynomial<int>(vector<int>()));
    check(Polynomial<int>(vector<int>{5, 0, 0, 0}), Polynomial<int>(vector<int>{5}));

    check(Polynomial<int>(vector<int>{}).Degree(), -1);
    check(Polynomial<int>(vector<int>{1}).Degree(), 0);
    check(Polynomial<int>(vector<int>{0, 1, 0, 0}).Degree(), 1);
    check(Polynomial<int>(vector<int>{0, 1, -5, 0}).Degree(), 2);

    check(Polynomial<int>(vector<int>{0, 1, -5, 0})[0], 0);
    check(Polynomial<int>(vector<int>{0, 1, -5, 0})[1], 1);
    check(Polynomial<int>(vector<int>{0, 1, -5, 0})[2], -5);
    check(Polynomial<int>(vector<int>{0, 1, -5, 0})[3], 0);

    check(Polynomial<int>(vector<int>{0, 1, 2, 3}) + Polynomial<int>(vector<int>{0, -1, 3}), Polynomial<int>(vector<int>{0, 0, 5, 3}));
    check(Polynomial<int>(vector<int>{}) + Polynomial<int>(vector<int>{0}), Polynomial<int>(vector<int>{}));
    check(Polynomial<int>(vector<int>{}) + Polynomial<int>(vector<int>{42}), Polynomial<int>(vector<int>{42}));
    check(Polynomial<int>(vector<int>{42}) + Polynomial<int>(vector<int>{}), Polynomial<int>(vector<int>{42}));
    check(Polynomial<int>(vector<int>{42}) + Polynomial<int>(vector<int>{-42}), Polynomial<int>(vector<int>{}));
    check(Polynomial<int>(vector<int>{-1, 1, -1, 1}) + Polynomial<int>(vector<int>{1, -1, 1, -1, 1}), Polynomial<int>(vector<int>{0, 0, 0, 0, 1}));
    check(Polynomial<int>(vector<int>{1, 0, 0, 0}) + Polynomial<int>(vector<int>{-1, 2, 3, 4, 0}), Polynomial<int>(vector<int>{0, 2, 3, 4}));

    check(Polynomial<int>(vector<int>{0, 1, 2, 3}) - Polynomial<int>(vector<int>{0, -1, 3}), Polynomial<int>(vector<int>{0, 2, -1, 3}));
    check(Polynomial<int>(vector<int>{}) - Polynomial<int>(vector<int>{0}), Polynomial<int>(vector<int>{}));
    check(Polynomial<int>(vector<int>{}) - Polynomial<int>(vector<int>{42}), Polynomial<int>(vector<int>{-42}));
    check(Polynomial<int>(vector<int>{42}) - Polynomial<int>(vector<int>{}), Polynomial<int>(vector<int>{42}));
    check(Polynomial<int>(vector<int>{42}) - Polynomial<int>(vector<int>{42}), Polynomial<int>(vector<int>{}));
    check(Polynomial<int>(vector<int>{-1, 1, -1, 1}) - Polynomial<int>(vector<int>{-1, 1, -1, 1, 1}), Polynomial<int>(vector<int>{0, 0, 0, 0, -1}));
    check(Polynomial<int>(vector<int>{1, 0, 0, 0}) - Polynomial<int>(vector<int>{1, 2, 3, 4, 0}), Polynomial<int>(vector<int>{0, -2, -3, -4}));

    check(*Polynomial<int>(vector<int>{0, 1, 2, 3}).begin(), 0);
    check(*Polynomial<int>(vector<int>{0, 1, 2, 3}).begin()+1, 1);
    check(*Polynomial<int>(vector<int>{0, 1, 2, 3}).begin()+2, 2);

    check(Polynomial<int>(vector<int>{5}) == 5, true);
    check(Polynomial<int>(vector<int>{5, 0, 0}) == 5, true);
    check(Polynomial<int>(vector<int>{}) == 1, false);
    check(Polynomial<int>(vector<int>{}) == 0, true);

    check(Polynomial<int>(vector<int>{1, 1}) * Polynomial<int>(vector<int>{-1, 1}), Polynomial<int>(vector<int>{-1, 0, 1}));
    check(Polynomial<int>(vector<int>{}) * Polynomial<int>(vector<int>{10}), Polynomial<int>(vector<int>{}));
    check(Polynomial<int>(vector<int>{10}) * Polynomial<int>(vector<int>{}), Polynomial<int>(vector<int>{}));
    check(Polynomial<int>(vector<int>{1, 1}) * Polynomial<int>(vector<int>{1, -1, 1}), Polynomial<int>(vector<int>{1, 0, 0, 1}));
    check(Polynomial<int>(vector<int>{-1, 1}) * Polynomial<int>(vector<int>{1, 1, 1}), Polynomial<int>(vector<int>{-1, 0, 0, 1}));

    check(Polynomial<int>(vector<int>{-1, 1})(1), 0);
    check(Polynomial<int>(vector<int>{})(1), 0);
    check(Polynomial<int>(vector<int>{5})(1), 5);
    check(Polynomial<int>(vector<int>{1, 2, 1})(-3), 4);

    check(Polynomial<int>(vector<int>{}) & Polynomial<int>(vector<int>{1, 2, 3}), 0);
    check(42 & Polynomial<int>(vector<int>{1, 2, 3}), 42);
    check(Polynomial<int>(vector<int>{1, 2, -1}) & Polynomial<int>(vector<int>{-1, 1}), Polynomial<int>(vector<int>{-2, 4, -1}));
    check(Polynomial<int>(vector<int>{1, 2, 3}) & Polynomial<int>(vector<int>{1}), 6);

    check(Polynomial<int>(vector<int>{0}) / Polynomial<int>(vector<int>{1}), 0);
    check(Polynomial<int>(vector<int>{0}) % Polynomial<int>(vector<int>{1}), 0);
    check(Polynomial<int>(vector<int>{42}) / Polynomial<int>(vector<int>{1, 1}), 0);
    check(Polynomial<int>(vector<int>{42}) % Polynomial<int>(vector<int>{1, 1}), 42);
    check(Polynomial<int>(vector<int>{2, 2}) / Polynomial<int>(vector<int>{2}), Polynomial<int>(vector<int>{1, 1}));
    check(Polynomial<int>(vector<int>{3, 2, 1}) / Polynomial<int>(vector<int>{2, 1}), Polynomial<int>(vector<int>{0, 1}));
    check(Polynomial<int>(vector<int>{3, 2, 1}) % Polynomial<int>(vector<int>{2, 1}), Polynomial<int>(vector<int>{3}));
    check(Polynomial<int>(vector<int>{1, 3, 0, 4}) / Polynomial<int>(vector<int>{1, 2}), Polynomial<int>(vector<int>{2, -1, 2}));
    check(Polynomial<int>(vector<int>{1, 3, 0, 4}) % Polynomial<int>(vector<int>{1, 2}), Polynomial<int>(vector<int>{-1}));

    check((Polynomial<int>(vector<int>{2, 2}), Polynomial<int>(vector<int>{1, 1})), Polynomial<int>(vector<int>{1, 1}));
    check((Polynomial<int>(vector<int>{1, 1}), Polynomial<int>(vector<int>{0, 2, 2})), Polynomial<int>(vector<int>{1, 1}));
    check((Polynomial<int>(vector<int>{24, -20, -8, 4}), Polynomial<int>(vector<int>{-4, 2, 2})), Polynomial<int>(vector<int>{-2, 1, 1}));
}


int main() {
    test();

    Polynomial<int> f1 = vector<int>{0};
    Polynomial<int> f2 = vector<int>{1};
    Polynomial<int> f3 = vector<int>{-1};
    Polynomial<int> f4 = vector<int>{10, 1, -1, 2, -2};
    Polynomial<int> f5 = vector<int>{1, 0, -1, 0, 5};
    Polynomial<int> f6 = vector<int>{6, 0, -1, 0, -1, 0, 0};
    Polynomial<int> f7 = vector<int>{-6, 0, -1, 0, -1, 0, 0};
    Polynomial<int> f8 = vector<int>{-1, -1, -6, 1, -5};

    //cout << (Polynomial<int>(vector<int>{24, -20, -8, 4}), Polynomial<int>(vector<int>{-4, 2, 2}), Polynomial<int>(vector<int>{-2, 1, 1}));

    /*
    cout << f1 << "\n";
    cout << f2 << "\n";
    cout << f3 << "\n";
    cout << f4 << "\n";
    cout << f5 << "\n";
    cout << f6 << "\n";
    cout << f7 << "\n";
    cout << f8 << "\n";
    */

    return 0;
}
