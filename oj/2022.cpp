// 单指针扫描，这题也可用二分查找找出离每一个数字最近的点

#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

ll abs_(ll a, ll b) { return llabs(a - b); }

vector<ll> solve(const vector<ll>& a, const vector<ll>& b) {
    vector<ll> res(a.size());
    int k = 0;
    for (int i = 0; i < a.size(); i++) {
        // 必须是 >= ，遇到数组中出现连续的相同值，需要保证指针向后移动
        while (k + 1 < b.size() && abs_(a[i], b[k]) >= abs_(a[i], b[k + 1])) {
            k++;
        }
        res[i] = abs_(a[i], b[k]);
    }
    return res;
}

ll max_(vector<ll> v1, vector<ll> v2) {
    ll max_num = 0;
    for (auto& i : v1) max_num = max(i, max_num);
    for (auto& i : v2) max_num = max(i, max_num);
    return max_num;
}

int main() {
    // m:0,n:1
    ll m, n;
    cin >> m >> n;

    vector<ll> ac_m(m), ac_n(n);
    for (ll i = 0; i < m; i++) cin >> ac_m[i];
    for (ll i = 0; i < n; i++) cin >> ac_n[i];
    sort(ac_m.begin(), ac_m.end());
    sort(ac_n.begin(), ac_n.end());

    vector<ll> res_1 = solve(ac_m, ac_n), res_2 = solve(ac_n, ac_m);
    cout << max_(res_1, res_2) << endl;
    return 0;
}