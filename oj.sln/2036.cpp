#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// 计算阶乘
int fun(int num) {
    int res = 1;
    for (int i = 1; i <= num; i++) {
        res *= i;
    }
    return res;
}

// 组合数
int C(int n, int k) { return fun(n) / fun(k) / fun(n - k); }

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> tall(n, 0);
    for (int i = 0; i < n; i++) {
        cin >> tall[i];
    }
    // 要先排序，因为unique只能去除相邻的重复元素
    sort(tall.begin(), tall.end());
    auto last = unique(tall.begin(), tall.end());
    tall.erase(last, tall.end());
    if (m > tall.size()) {
        cout << 0 << endl;
    } else {
        // 在num个不一样的数字中，找到多少个长度为size的降序序列，其实就是组合数的计算
        cout << C(tall.size(), m) << endl;
    }
    return 0;
}