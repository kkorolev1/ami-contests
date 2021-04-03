#include <iostream>
#include <vector>

template <typename T>
class MathVector {
private:
    std::vector<T> data;

public:
    // Zero vector of size n
    MathVector(size_t n) {
        data.resize(n, 0);
    }

    template <typename Iter>
    MathVector(Iter first, Iter last) {
        while (first != last)
            data.push_back(*first++);
    }

    size_t Dimension() const {
        return data.size();
    }

    T& operator[] (size_t i) {
        return data[i];
    }

    const T& operator[] (size_t i) const {
        return data[i];
    }
};


// Output format: (1, 2, 3, 4, 5)
template <typename T>
std::ostream& operator << (std::ostream& out, const MathVector<T>& v) {
    out << '(';
    for (size_t i = 0; i != v.Dimension(); ++i) {
        if (i > 0)
            out << ", ";
        out << v[i];
    }
    out << ')';
    return out;
}

template <typename T>
MathVector<T>& operator *= (MathVector<T>& v, const T& scalar) {
    for (size_t i = 0; i != v.Dimension(); ++i)
        v[i] *= scalar;
    return v;
}

template <typename T>
MathVector<T> operator * (const MathVector<T>& v, const T& scalar) {
    auto tmp(v);
    tmp *= scalar;
    return tmp;
}

template <typename T>
MathVector<T> operator * (const T& scalar, const MathVector<T>& v) {
    return v * scalar;
}

template <typename T>
MathVector<T>& operator+=(MathVector<T>& v, const MathVector<T>& u) {
    for (size_t i = 0; i != v.Dimension(); ++i)
        v[i] += u[i];
    return v;
}

template <typename T>
MathVector<T> operator+(const MathVector<T>& v, const MathVector<T>& u) {
    auto tmp(v);
    tmp += u;
    return tmp;
}


#include <iostream>

using namespace std;

int main() {
    vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8};
    MathVector<int> v1(nums.begin(), nums.begin() + 3);
    MathVector<int> v2(nums.begin() + 3, nums.begin() + 6);
    auto v3 = v1 + v2;

    cout << v1 << "\n";
    v1 += v3;

    cout << v1 << "\n";
    cout << v2 << "\n";
    cout << v3 << "\n";

    MathVector<int> v4(0);
    cout << v4 << "\n";

    return 0;
}
