#include <iostream>
#include <vector>

using namespace std;

using std::vector;

class Minesweeper {
private:
    size_t M, N;
    vector<vector<int>> Table;

public:
    Minesweeper(size_t m, size_t n): M(m), N(n) {
        Table.resize(M);
        for (auto& row : Table)
            row.resize(N);
    }

    size_t Rows() const {
        return M;
    }

    size_t Columns() const {
        return N;
    }

    void SetMine(size_t i, size_t j) {
        Table[i][j] = -1;
    }

    int operator () (size_t i, size_t j) const {
        return Table[i][j];
    }

    void CheckForMinesAround() {
        for (size_t i = 0; i != M; ++i)
            for (size_t j = 0; j != N; ++j)
                if (Table[i][j] != -1)
                    CheckForMinesAround(i, j);
    }

private:
    void CheckForMinesAround(size_t i, size_t j) {
        int counter = 0;
        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                size_t x = i + dx;
                size_t y = j + dy;

                if (x < M && y < N &&
                    Table[x][y] == -1) {
                    ++counter;
                }
            }
        }
        Table[i][j] = counter;
    }
};

std::ostream& operator << (std::ostream& out, const Minesweeper& ms) {
    for (size_t i = 0; i != ms.Rows(); ++i) {
        for (size_t j = 0; j != ms.Columns(); ++j) {
            if (ms(i, j) == -1)
                out << '*';
            else
                out << ms(i, j);
        }
        out << "\n";
    }

    out << "\n";
    return out;
}

int main() {
    freopen("input.txt", "r", stdin);
    size_t m, n;
    std::cin >> m >> n;
    Minesweeper ms(m, n);

    int minesCount;
    std::cin >> minesCount;
    while (minesCount-->0) {
        size_t x, y;
        std::cin >> x >> y;
        ms.SetMine(x, y);
    }

    ms.CheckForMinesAround();

    std::cout << ms;
    return 0;
}
