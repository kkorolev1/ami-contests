#include <iostream>
#include <vector>
using namespace std;

int main() {
    freopen("input.txt", "r", stdin);
    ios::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> arr1(n);

    for (int i = 0; i < n; ++i)
        cin >> arr1[i];

    int m;
    cin >> m;

    vector<int> arr2(m);

    for (int i = 0; i < m; ++i)
        cin >> arr2[i];

    int ans_l = 0, ans_r = 0;
    int l = 0, r = 0;

    while (l < n && r < m) {
        while (r < m && arr1[l] >= arr2[r]) {
            if (abs(arr1[ans_l] - arr2[ans_r]) > abs(arr1[l] - arr2[r])) {
                ans_l = l, ans_r = r;
            }
            ++r;
        }
        while (l < n && arr2[r] >= arr1[l]) {
            if (abs(arr1[ans_l] - arr2[ans_r]) > abs(arr1[l] - arr2[r])) {
                ans_l = l, ans_r = r;
            }
            ++l;
        }
    }

    cout << arr1[ans_l] << " " << arr2[ans_r] << "\n";

    return 0;
}
