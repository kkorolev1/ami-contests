#include <vector>

std::vector<std::vector<int>> Transpose(const std::vector<std::vector<int>>& matrix) {
    if (matrix.empty()) {
        return std::vector<std::vector<int>>{};
    }

    size_t n = matrix.size();
    size_t m = matrix.front().size();
    std::vector<std::vector<int>> res(m, std::vector<int>(n));

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j) {
            res[j][i] = matrix[i][j];
        }
    }

    return res;
}

#include <iostream>

int main() {
    std::vector<std::vector<int>> v = {{1, 2, 3, 4}, {5, 6, 7, 8}};
    auto transposed = Transpose({{}, {}, {}});

    for (auto& row : transposed) {
        for (int x : row) {
            std::cout << x << " ";
        }
        std::cout << "\n";
    }

    return 0;
}