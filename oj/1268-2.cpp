#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> nums(n, 0);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    // 定义d[i]为以序号i结尾的子段的最大和
    vector<int> dp(n, 0);
    dp[0] = nums[0];
    int max = dp[0];
    for (int i = 1; i < n; i++) {
        // 只需要区分前面部分字段是否为正数
        dp[i] = dp[i - 1] >= 0 ? dp[i - 1] + nums[i] : nums[i];
        if (max < dp[i]) max = dp[i];
    }
    cout << max;
    return 0;
}