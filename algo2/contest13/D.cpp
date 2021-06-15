#include <iostream>
#include <vector>
#include <array>
using namespace std;

struct Box {
    int a, b, c, i;

    array<Box, 6> rotations() {
        return {Box{a,b,c,i},{a,c,b,i},{b,a,c,i},{b,c,a,i},{c,a,b,i},{c,b,a,i}};
    }
};

struct BoxSolver {
    int n;
    vector<Box> boxes;
    int max_h = 0;

    vector<Box> cur_tower, ans_tower;
    vector<bool> used;

    BoxSolver(int n) : n(n), boxes(n), used(n) {}

    void read() {
        for (int i = 0; i < n; ++i) {
            auto& [a, b, c, idx] = boxes[i];
            cin >> a >> b >> c;
            idx = i + 1;
        }
    }

    void solve(int step, int h) {
        bool can_place = false;

        for (int i = 0; i < n; ++i) {
            if (!used[i]) {
                auto& box = boxes[i];
                for (auto& rotated_box : box.rotations()) {
                    if (step > 0) {
                        auto& prev_box = cur_tower[step-1];
                        if (prev_box.a < rotated_box.a || prev_box.b < rotated_box.b) {
                            continue;
                        }
                    }
                    used[i] = true;
                    cur_tower.push_back(rotated_box);
                    can_place = true;
                    solve(step+1, h + rotated_box.c);
                    used[i] = false;
                    cur_tower.pop_back();
                }
            }
        }

        if (!can_place) {
            if (h > max_h) {
                max_h = h;
                ans_tower = cur_tower;
            }
        }

    }

    static void merge(vector<Box>& arr1, vector<Box>& arr2) {
        int l = 0, r = 0;
        int n1 = arr1.size(), n2 = arr2.size();

        vector<Box> ans;
        ans.reserve(n1 + n2);

        while (l < n1 && r < n2) {
            if (max(arr1[l].a, arr1[l].b) > max(arr2[r].a, arr2[r].b)) {
                ans.push_back(arr1[l++]);
            } else {
                ans.push_back(arr2[r++]);
            }
        }
    }

    void print_ans() {
        cout << max_h << "\n";
        cout << ans_tower.size() << "\n";

        for (auto& [a, b, c, i] : ans_tower) {
            cout << i << " " << a << " " << b << " " << c << "\n";
        }
    }
};



int main() {
    freopen("input.txt", "r", stdin);
    ios::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    BoxSolver solver1(n / 2);
    BoxSolver solver2(n - n / 2);

    solver1.read();
    solver2.read();

    solver1.solve(0, 0);
    solver2.solve(0, 0);

    solver1.print_ans();
    cout << "\n\n\n";
    solver2.print_ans();

    return 0;
}
