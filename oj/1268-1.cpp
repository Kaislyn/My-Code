#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int maxSubArray(const vector<int>& a, int l, int r) {
    if (l == r) return a[l];  // 只有一个元素
    int mid = (l + r) / 2;

    // 左半最大子段和
    int left_sum = maxSubArray(a, l, mid);
    // 右半最大子段和
    int right_sum = maxSubArray(a, mid + 1, r);

    // 计算跨越中间的最大子段和
    // 向左扩展（必须包含 a[mid]）
    int left_max = a[mid];
    int sum = 0;
    for (int i = mid; i >= l; --i) {
        sum += a[i];
        left_max = max(left_max, sum);
    }
    // 向右扩展（必须包含 a[mid+1]）
    int right_max = a[mid + 1];
    sum = 0;
    for (int i = mid + 1; i <= r; ++i) {
        sum += a[i];
        right_max = max(right_max, sum);
    }
    int cross_sum = left_max + right_max;

    // 返回三者最大值
    return max({left_sum, right_sum, cross_sum});
}

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    cout << maxSubArray(a, 0, n - 1) << endl;
    return 0;
}