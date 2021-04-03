#include <iostream>
#include <vector>
using namespace std;

template <typename T>
class Matrix {
public:
    using Row = vector<T>;

    Matrix(const vector<Row>& rows) : rows_(rows) {}

    friend ostream& operator<<(ostream& os, const Matrix& mat) {
        for (size_t i = 0; i < mat.rows(); ++i) {
            for (size_t j = 0; j < mat.cols(); ++j) {
                os << mat(i, j);
                if (j + 1 != mat.cols())
                    os << "\t";
            }
            if (i + 1 != mat.rows())
                os << "\n";
        }
        return os;
    }

    inline pair<size_t, size_t> size() const { return {rows(), cols()}; }
    inline size_t rows() const { return rows_.size(); }
    inline size_t cols() const { return rows_[0].size(); }

    T& operator()(size_t i, size_t j) { return rows_[i][j]; }
    const T& operator()(size_t i, size_t j) const { return rows_[i][j]; }

    Matrix& operator+=(const Matrix& other) {
        for (size_t i = 0; i < rows(); ++i) {
            for (size_t j = 0; j < cols(); ++j) {
                this->operator()(i, j) += other(i, j);
            }
        }
        return *this;
    }

    Matrix operator+(const Matrix& other) const {
        Matrix res = *this;
        res += other;
        return res;
    }

    template <typename S>
    Matrix& operator*=(const S& scalar) {
        for (size_t i = 0; i < rows(); ++i) {
            for (size_t j = 0; j < cols(); ++j) {
                this->operator()(i, j) += scalar;
            }
        }
        return *this;
    }

    template<typename S>
    Matrix operator*(const S& scalar) const {
        Matrix res = *this;
        res *= scalar;
        return res;
    }

    Matrix& transpose() {
        auto [rows, cols] = size();
        vector<vector<T>> buffer(cols, vector<T>(rows));

        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                buffer[j][i] = rows_[i][j];
            }
        }

        rows_.swap(buffer);
        return *this;
    }

    Matrix transposed() const {
        Matrix res(*this);
        res.transpose();
        return res;
    }

private:
    vector<Row> rows_;
};

int main() {
    vector<vector<int>> xs = {{1, 2, 3}, {4, 5, 6}};
    vector<vector<int>> ys = {{1, 2, 3}, {4, 5, 6}};
    Matrix<int> mat1(xs), mat2(ys);
    mat1 += mat2;
    cout << mat1 << "\n\n";

    mat1.transpose();
    cout << mat1 << "\n\n";

    auto mat3 = mat2.transposed();
    cout << mat3 << "\n";

    return 0;
}
