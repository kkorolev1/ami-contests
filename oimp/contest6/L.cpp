#include <algorithm>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

template <typename T>
class Polynomial {
public:
    Polynomial(const vector<T>& coeffs) :
        Polynomial(coeffs.begin(), coeffs.end()) {}

    Polynomial(const T& value = T()) : Polynomial(vector<T>(1, value)) {}

    template <typename Iter>
    Polynomial(Iter first, Iter last) {
        size_t deg = 0;

        for (auto it = first; it != last; ++it, ++deg) {
            if (*it != ZERO)
                coeffs_[deg] = *it;
        }
    }

    bool operator==(const Polynomial& other) const {
        return coeffs_ == other.coeffs_;
    }

    bool operator!=(const Polynomial& other) const {
        return !(*this == other);
    }

    Polynomial& operator+=(const Polynomial& other) {
        for (auto& [deg, coef] : coeffs_) {
            auto it = other.coeffs_.find(deg);
            if (it != other.coeffs_.end())
                coef += it->second;
        }

        for (auto& [deg, coef] : other.coeffs_) {
            auto it = coeffs_.find(deg);
            if (it == coeffs_.end())
                coeffs_.emplace(deg, coef);
        }

        removeZeroes();
        return *this;
    }

    Polynomial& operator-=(const Polynomial& other) {
        for (auto& [deg, coef] : coeffs_) {
            auto it = other.coeffs_.find(deg);
            if (it != other.coeffs_.end())
                coef -= it->second;
        }

        for (auto& [deg, coef] : other.coeffs_) {
            auto it = coeffs_.find(deg);
            if (it == coeffs_.end())
                coeffs_.emplace(deg, -coef);
        }

        removeZeroes();
        return *this;
    }


    Polynomial& operator*=(const Polynomial& other) {
        map<size_t, T> coeffs;

        for (auto& [deg, coef] : coeffs_) {
            for (auto& [otherDeg, otherCoef] : other.coeffs_) {
                coeffs[deg + otherDeg] += coef * otherCoef;
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
        auto it = coeffs_.find(degree);
        if (it == coeffs_.end())
            return ZERO;
        return it->second;
    }

    int Degree() const {
        if (coeffs_.empty())
            return -1;
        return prev(coeffs_.end())->first;
    }

    T operator()(const T& arg) const {
        T res(0);

        for (int deg = Degree(); deg >= 0; --deg) {
            res = this->operator[](deg) + res * arg;
        }

        return res;
    }


    friend ostream& operator<<(ostream& os, const Polynomial& poly) {
        if (poly.coeffs_.empty()) {
            os << ZERO;
            return os;
        }

        for (auto it = poly.coeffs_.rbegin(); it != poly.coeffs_.rend(); ++it) {
            const auto& val = it->second;
            int deg = it->first;

            if (val != ZERO) {
                if (val > ZERO) {
                    if (deg != poly.Degree())
                        os << "+";
                    if (deg == 0 || val != T(1))
                        os << val;
                } else {
                    if (deg == 0 || val != T(-1))
                        os << val;
                    else
                        os << "-";
                }

                if (deg >= 1 && (val != T(1) && val != T(-1)))
                    os << "*";

                if (deg >= 1)
                    os << "x";

                if (deg >= 2)
                    os << "^" << deg;
            }
        }

        return os;
    }

    using Iterator = typename map<size_t, T>::const_iterator;

    Iterator begin() const { return coeffs_.begin(); }
    Iterator end() const { return coeffs_.end(); }

    friend Polynomial operator&(const Polynomial& lhs, const Polynomial& rhs) {
        if (lhs.coeffs_.empty())
            return Polynomial();

        Polynomial res(lhs[0]);
        auto powers_of_rhs = rhs;

        for (int deg = 1; deg <= lhs.Degree(); ++deg) {
            res += lhs[deg] * powers_of_rhs;
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

        return p / p.highestDeg();
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
            const auto& d = cur_poly.highestDeg() / rhs.highestDeg();
            auto deg = cur_poly.Degree() - rhs.Degree();
            vector<T> coeffs(deg + 1, ZERO);
            coeffs[deg] = d;
            Polynomial tmp(coeffs);

            q += tmp;
            cur_poly -= tmp * rhs;
        }

        return {q, cur_poly};
    }

    const T& highestDeg() const {
        return this->operator[](Degree());
    }

    void removeZeroes() {
        for (auto it = coeffs_.begin(); it != coeffs_.end(); )
            if (it->second == ZERO)
                it = coeffs_.erase(it);
            else
                ++it;
    }

private:
    static T ZERO;
    map<size_t, T> coeffs_;
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

    check(Polynomial<int>(vector<int>{0, 1, 2, 3}).begin()->second, 1);
    check(next(Polynomial<int>(vector<int>{0, 1, 2, 3}).begin())->second, 2);
    check(next(Polynomial<int>(vector<int>{0, 1, 2, 3}).begin(), 2)->second, 3);

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
    check(Polynomial<int>(vector<int>{0, -2, 0, 3})(-1), -1);

    check(Polynomial<int>(vector<int>{}) & Polynomial<int>(vector<int>{1, 2, 3}), 0);
    check(42 & Polynomial<int>(vector<int>{1, 2, 3}), 42);
    check(Polynomial<int>(vector<int>{1, 2, -1}) & Polynomial<int>(vector<int>{-1, 1}), Polynomial<int>(vector<int>{-2, 4, -1}));
    check(Polynomial<int>(vector<int>{1, 2, 3}) & Polynomial<int>(vector<int>{1}), 6);
    check(Polynomial<int>(vector<int>{0, -2, 0, 2}) & Polynomial<int>(vector<int>{0, 1, 1}), Polynomial<int>(vector<int>{0, -2, -2, 2, 6, 6, 2}));

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
    try {
        test();

        Polynomial<int> f1 = vector<int>{0};
        Polynomial<int> f2 = vector<int>{1};
        Polynomial<int> f3 = vector<int>{-1};
        Polynomial<int> f4 = vector<int>{10, 1, -1, 2, -2};
        Polynomial<int> f5 = vector<int>{1, 0, -1, 0, 5};
        Polynomial<int> f6 = vector<int>{6, 0, -1, 0, -1, 0, 0};
        Polynomial<int> f7 = vector<int>{-6, 0, -1, 0, -1, 0, 0};
        Polynomial<int> f8 = vector<int>{0, 0, -1, -1, -6, 1, -5, 0};


        cout << f1 << "\n";
        cout << f2 << "\n";
        cout << f3 << "\n";
        cout << f4 << "\n";
        cout << f5 << "\n";
        cout << f6 << "\n";
        cout << f7 << "\n";
        cout << f8 << "\n";
    } catch (std::exception& ex) {
        cout << ex.what() << "\n";
    }



    return 0;
}
