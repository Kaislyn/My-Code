// 连续子数组和不超过 V 的最大值
/**
 * 这个滑动窗口算法维护的是 以当前右端点 right 结尾的、和不超过 V 的最长（即和最大）的连续子数组。
 * 因为所有数都是正整数，子数组越长，和就越大，所以只要保证和不超过 V，窗口尽可能长就能得到以该位置结尾的最大和。
 */

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
    int left = 0, right = 0, sum = 0, ans = 0;
    for (; right < n; right++) {
        sum += a[right];
        while (sum > v) {
            sum -= a[left];
            left++;
        }
        if (sum == v) {
            cout << v << endl;
            return 0;
        }
        ans = max(ans, sum);
    }
    cout << ans << endl;
    return 0;
}