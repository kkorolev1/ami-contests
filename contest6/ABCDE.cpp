#include <algorithm>
#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

template <typename T>
class Matrix {
    vector<vector<T>> v;

public:
    Matrix(const vector<vector<T>>& v) : v(v) {}

    pair<size_t, size_t> size() const {
        return {v.size(), v[0].size()};
    }

    Matrix& operator += (const Matrix& other) {
        for (size_t i = 0; i != v.size(); ++i) {
            for (size_t j = 0; j != v[0].size(); ++j) {
                v[i][j] += other.v[i][j];
            }
        }
        return *this;
    }

    Matrix operator + (const Matrix& other) const {
        Matrix res = *this;
        res += other;
        return res;
    }

    template<typename S>
    Matrix& operator *= (const S& scalar) {
        for (size_t i = 0; i != v.size(); ++i) {
            for (size_t j = 0; j != v[0].size(); ++j) {
                v[i][j] *= scalar;
            }
        }
        return *this;
    }

    template<typename S>
    Matrix operator * (const S& scalar) const {
        Matrix res = *this;
        res *= scalar;
        return res;
    }

    template <typename U>
    friend ostream& operator<<(ostream& out, const Matrix<U>& m);

    Matrix& transpose() {
        *this = transposed();
        return *this;
    }

    Matrix transposed() const {
        auto [rows, cols] = size();
        vector<vector<T>> buffer(cols, vector<T>(rows));

        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                buffer[j][i] = v[i][j];
            }
        }

        return Matrix(buffer);
    }

    Matrix& operator*=(const Matrix& other) {
        *this = *this * other;
        return *this;
    }

    Matrix operator*(const Matrix& other) const {
        auto [rows, cols] = size();
        auto [otherRows, otherCols] = other.size();
        assert(cols == otherRows);

        vector<vector<T>> buffer(rows, vector<T>(otherCols));

        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < otherCols; ++j) {
                for (size_t k = 0; k < cols; ++k) {
                    buffer[i][j] += v[i][k] * other.v[k][j];
                }
            }
        }

        return Matrix(buffer);
    }

    template <typename Impl>
    class BaseIterator {
    public:
        BaseIterator(size_t i, size_t j) : i_(i), j_(j) {}

        Impl& impl() { return static_cast<Impl&>(*this); }
        const Impl& impl() const { return static_cast<const Impl&>(*this); }

        BaseIterator& operator++() {
            if (j_ + 1 == impl().matrix().size().second) {
                j_ = 0;
                ++i_;
            } else {
                ++j_;
            }
            return *this;
        }

        BaseIterator operator++(int) {
            Iterator tmp(*this);
            ++*this;
            return tmp;
        }

        bool operator==(const BaseIterator& other) const {
            return &impl().matrix() == &impl().matrix() &&
                i_ == other.i_ && j_ == other.j_;
        }

        bool operator!=(const BaseIterator& other) const { return !(*this == other); }

    protected:
        size_t i_, j_;
    };

    class Iterator : public BaseIterator<Iterator> {
    public:
        Iterator(Matrix& mat, size_t i, size_t j) :
            BaseIterator<Iterator>(i, j), mat_(mat) {}
        T& operator*() { return mat_.v[this->i_][this->j_]; }
        const Matrix& matrix() const { return mat_; }
    private:
        Matrix& mat_;
    };

    class ConstIterator : public BaseIterator<ConstIterator> {
    public:
        ConstIterator(const Matrix& mat, size_t i, size_t j) :
            BaseIterator<ConstIterator>(i, j), mat_(mat) {}
        const T& operator*() const { return mat_.v[this->i_][this->j_]; }
        const Matrix& matrix() const { return mat_; }
    private:
        const Matrix& mat_;
    };

    Iterator begin() { return Iterator(*this, 0, 0); }
    Iterator end() { return Iterator(*this, size().first, 0); }
    ConstIterator begin() const { return ConstIterator(*this, 0, 0); }
    ConstIterator end() const { return ConstIterator(*this, size().first, 0); }
};

template <typename U>
ostream& operator<<(ostream& out, const Matrix<U>& m) {
    auto [h, w] = m.size();

    for (size_t i = 0; i < h; ++i) {
        for (size_t j = 0; j < w; ++j) {
            out << m.v[i][j];
            if (j != w - 1)
                out << '\t';
        }
        if (i != h - 1)
            out << '\n';
    }

    return out;
}


#include <algorithm>
#include <random>
#include "../contest5/P.cpp"


Matrix<int> genMatrix(size_t rows, size_t cols) {
    vector<vector<int>> v(rows, vector<int>(cols));
    random_device rd{};
    std::seed_seq seed{rd(), rd(), rd(), rd(), rd()};
    mt19937 g(seed);
    uniform_int_distribution d(1, 100);

    for (auto& row : v) {
        generate(row.begin(), row.end(), [&]() { return d(g); });
    }

    return Matrix<int>(v);
}

int main() {
    const size_t rows = 3;
    const size_t cols = 3;

    const Matrix<int> cmat = genMatrix(rows, cols);
    // auto m2 = genMatrix(cols, rows);
    cout << cmat << "\n";

    for (auto it = cmat.begin(); it != cmat.end(); ++it) {
        cout << *it << "\n";
    }
}
