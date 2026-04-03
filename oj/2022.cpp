#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    // m:0,n:1
    int m, n;
    cin >> m >> n;
    vector<int> ac_m(m, 0), ac_n(n, 0);
    for (auto& i : ac_m) cin >> i;
    for (auto& j : ac_n) cin >> j;
    sort(ac_m.begin(), ac_m.end());
    sort(ac_n.begin(), ac_n.end());

    // 题目示例：
    // 1 2 3 4 5 6
    // 3 6 8 9 11

    int i = 0, j = 0;
    int ans_ds = abs(ac_m[0] - ac_n[0]);

    for (; i < m; i++) {
        int _1 = abs(ac_m[i] - ac_n[j]), _2 = abs(ac_m[i] - ac_n[j + 1]);
        if (_1 < _2) {
            if (j < n - 1) j++;
        }
        ans_ds = max(ans_ds, _1 > _2 ? _1 : _2);
    }

    cout << ans_ds << endl;
    return 0;
}