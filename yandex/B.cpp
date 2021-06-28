#include <iostream>
#include <vector>

using namespace std;

struct Seats {
    vector<int> win_l, win_r, aisle_l, aisle_r;
    vector<string> seats;

    Seats(int n) : win_l(n), win_r(n), aisle_l(n), aisle_r(n), seats(n) {}

    void read_row(int i) {
        auto& row = seats[i];
        cin >> row;

        auto left_side = row.substr(0, SIDE_SEATS);
        auto right_side = row.substr(SIDE_SEATS+1);

        win_l[i] = count_left(left_side);
        win_r[i] = count_right(right_side);
        aisle_l[i] = count_right(left_side);
        aisle_r[i] = count_left(right_side);
    }

    bool find_seats(int num, const string& side, const string& pos) {
        int row = -1;
        using f = function<int(int)>;
        f f1, f2;

        if (side == "left") {
            if (pos == "window") {
                if ((row = find_seats(win_l, num)) == -1) {
                    return false;
                }

                aisle_l[row] = min(0, aisle_l[row] - num);
                f1 = f2 = [](int i) { return i; };

            } else {
                if ((row = find_seats(aisle_l, num)) == -1) {
                    return false;
                }

                win_l[row] = min(0, win_l[row] - num);
                f1 = f2 = [&](int i) { return SIDE_SEATS-num+i; };
            }
        } else {
            if (pos == "window") {
                if ((row = find_seats(win_r, num)) == -1) {
                    return false;
                }

                aisle_r[row] = min(0, aisle_r[row] - num);
                f1 = [&](int i) { return 2*SIDE_SEATS-num+i; };
                f2 = [&](int i) { return 2*SIDE_SEATS-num+i+1; };

            } else {
                if ((row = find_seats(aisle_r, num)) == -1) {
                    return false;
                }

                win_r[row] = min(0, win_r[row] - num);
                f1 = [&](int i) { return SIDE_SEATS+i; };
                f2 = [&](int i) { return SIDE_SEATS+1+i; };
            }
        }

        cout << "Passengers can take seats:";

        for (int i = 0; i < num; ++i) {
            cout << " " << row+1 << SEATS_STR[f1(i)];
            seats[row][f2(i)] = 'X';
        }

        return true;
    }

    void print() {
        cout << "\n";
        for (auto& row : seats) {
            cout << row << "\n";
        }
    }

    static inline const int SIDE_SEATS = 3;
    static inline const string SEATS_STR = "ABCDEF";
private:

    int count_left(const string& row) {
        int index = row.find('#');
        return index != -1 ? index : SIDE_SEATS;
    }

    int count_right(const string& row) {
        int index = row.rfind('#');
        return index != -1 ? SIDE_SEATS-index-1 : SIDE_SEATS;
    }

    int find_seats(vector<int>& arr, int num) {
        for (int row = 0; row < arr.size(); ++row) {
            if (arr[row] >= num) {
                arr[row] = 0;
                return row;
            }
        }
        return -1;
    }
};

int main() {
    ios::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;
    cin >> n;

    Seats seats(n);

    for (int i = 0; i < n; ++i) {
        seats.read_row(i);
    }

    int m;
    cin >> m;

    for (int i = 0; i < m; ++i) {
        int num;
        string side, pos;
        cin >> num >> side >> pos;
        if (!seats.find_seats(num, side, pos)) {
            cout << "Cannot fulfill passengers requirements\n";
            continue;
        }
        seats.print();
    }

    return 0;
}
