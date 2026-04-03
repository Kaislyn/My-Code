// 连续子数组和不超过 V 的最大值

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, v;
    cin >> n >> v;
    vector<int> a(n, 0);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int left = 0, right, sum, ans;
    for (right = 0; right < n; right++) {
        sum += a[right];
        while (sum > v) {
            sum -= a[left];
            left++;
        }
        ans = max(ans, sum);
    }
    cout << ans << endl;
    return 0;
}