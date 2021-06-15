#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

using Vec2 = pair<int, int>;

int main() {
    ios::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // freopen("input.txt", "r", stdin);

    int n, m;
    cin >> n >> m;

    vector<Vec2> arr(2 * m + 1);
    arr[2 * m] = Vec2{n, 1};

    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        arr[2 * i] = Vec2{a, 1};
        arr[2 * i + 1] = Vec2{b, 2};
    }

    sort(arr.begin(), arr.end());

    long long ans = 0;
    int counter = 0;
    int segment_end = -1;

    for (auto& [value, type] : arr) {
        if (type == 1) {
            if (counter == 0) {
                ans += value - segment_end - 1;
            }
            ++counter;
        } else {
            --counter;
            segment_end = value;
        }
    }

    cout << ans << "\n";

    return 0;
}
