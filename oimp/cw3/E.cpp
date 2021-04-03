#include <iostream>
#include <vector>

using namespace std;

template <typename T>
class Table {
public:
    Table(size_t rows, size_t cols) : data(rows, vector<T>(cols)) {}

    vector<T>& operator[](size_t i) {
        return data[i];
    }

    const vector<T>& operator[](size_t i) const {
        return data[i];
    }

    void resize(size_t rows, size_t cols) {
        data.resize(rows);

        for (auto& row : data)
            row.resize(cols);
    }

    pair<size_t, size_t> size() const {
        return {data.size(), !data.empty() ? data.front().size() : 0};
    }

private:
    vector<vector<T>> data;
};

int main() {
    Table<int> table(2, 2);
    table[0][0] = 1;
    table[0][1] = 2;
    table[1][0] = 3;
    table[1][1] = 4;
    table.resize(3, 3);

    return 0;
}
