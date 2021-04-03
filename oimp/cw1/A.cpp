#include <iostream>

#include <vector>
#include <string>
using namespace std;

bool isUpperTriangular(const std::vector<std::vector<int>>& matrix) {
    const auto n = matrix.size();

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            if (i > j && matrix[i][j] != 0)
                return false;
        }
    }
    return true;
}

bool isLowerTriangular(const std::vector<std::vector<int>>& matrix) {
    const auto n = matrix.size();

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            if (i < j && matrix[i][j] != 0)
                return false;
        }
    }
    return true;
}

std::string FindMatrixKind(const std::vector<std::vector<int>>& matrix) {
    bool isUpper = isUpperTriangular(matrix);
    bool isLower = isLowerTriangular(matrix);

    if (isUpper && isLower)
        return "Diagonal";
    else if (isUpper)
        return "UpperTriangular";
    else if (isLower)
        return "LowerTriangular";
    else
        return "Unknown";
}

int main() {
    vector<vector<int>> xs = {{5, 0, 0}, {0, 2, 0}, {0, 0, 1}};
    cout << FindMatrixKind(xs);
    return 0;
}
