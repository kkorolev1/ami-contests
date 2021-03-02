#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

template <typename T>
class Matrix {
public:
    using Row = vector<T>;

    Matrix(const vector<Row>& rows) :
        m_(rows.size()), n_(!rows.empty() ? rows[0].size() : 0) {
        rows_.resize(m_);

        for (size_t i = 0; i < m_; ++i) {
            rows_[i].resize(n_);
            copy(rows[i].begin(), rows[i].end(), rows_[i].begin());
        }
    }

    friend ostream& operator<<(ostream& os, const Matrix& mat) {
        for (size_t i = 0; i < mat.m_; ++i) {
            for (size_t j = 0; j < mat.n_; ++j) {
                os << mat(i, j);
                if (j + 1 != mat.n_)
                    os << "\t";
            }
            os << "\n";
        }
        return os;
    }

    pair<size_t, size_t> size() const {
        return make_pair(m_, n_);
    }

    T& operator()(size_t i, size_t j) {
        return rows_[i][j];
    }

    const T& operator()(size_t i, size_t j) const {
        return rows_[i][j];
    }

private:
    vector<Row> rows_;
    size_t m_, n_;
};

int main() {
    vector<vector<int>> xs = {{1, 2, 3}, {4, 5, 6}};
    Matrix<int> mat(xs);
    xs[0][0] = 3;
    cout << mat << "\n";
    return 0;
}
