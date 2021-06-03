#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

struct LongInt {
    string data;
    bool is_pos = true;

    friend istream& operator>>(istream& is, LongInt& x) {
        is >> x.data;
        reverse(x.data.begin(), x.data.end());
        if (x.data.back() == '-') {
            x.is_pos = false;
            x.data.pop_back();
        }
        return is;
    }

    friend bool operator==(const LongInt& x, const LongInt& y) {
        return x.data == y.data;
    }

    LongInt operator^(const LongInt& p) {
        if (!p.is_even())
            return (*this)^(p.subOne()) * (*this);
        auto tmp = (*this)^(p.divBy2());
        return tmp * tmp;
    }

    // TODO: Handle negative objs
    LongInt subOne() const {
        if (data.back() == '0')
            return LongInt{"1", false};
        LongInt res(*this);

        for (int i = 0; i < data.size(); ++i) {
            if (get(i) - 1 >= 0) {
                res.set(i, get(i) - 1);
                break;
            } else {
                res.set(i, 9);
            }
        }

        res.removeTrailingZeroes();
        return res;
    }

    LongInt divBy2() const {
        LongInt res;

        int index = data.size() - 1;
        int tmp = get(index);
        while (tmp < 2)
            tmp = 10 * tmp + get(--index);

        while (index >= 0) {
            res.data += (tmp / 2) + '0';
            tmp = (tmp % 2) * 10 + get(--index);
        }

        if (res.data.empty())
            return LongInt{"0"};

        reverse(res.data.begin(), res.data.end());
        return res;
    }

    friend LongInt operator*(const LongInt& lhs, const LongInt& rhs) {
        //TODO
        return LongInt();
    }

    LongInt operator%(const LongInt& d) {

    }

    bool is_even() const {
        return (get(0) % 2) == 0;
    }

    void removeTrailingZeroes() {
        auto rit = std::find_if(data.rbegin(), data.rend(),
                                [](char c) { return c != '0'; });
        data.erase(rit.base(), data.end());
        if (data.empty())
            data.push_back('0');
    }

    inline int get(int i) const {
        return data[i] - '0';
    }

    inline void set(int i, int value) {
        data[i] = value + '0';
    }
};

int main() {
    freopen("input.txt", "r", stdin);
    LongInt a, b, c, d;
    cin >> a >> b >> c >> d;

    cout << (a.divBy2() == b);
    //cout << (((a^b) == (c^d)) ? "correct\n" : "incorrect\n");

    return 0;
}
