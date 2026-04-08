#include <iostream>
#include <vector>
using namespace std;

const int MAX = 1e5;
vector<long long> pow2, pow3;  // 改用long long防溢出

// 预处理2和3的幂次
void precompute() {
    long long num = 1;
    // 生成2的幂
    while (num < MAX) {
        pow2.push_back(num);
        if (num > MAX / 2) break;
        num *= 2;
    }
    // 生成3的幂
    num = 1;
    while (num < MAX) {
        pow3.push_back(num);
        if (num > MAX / 3) break;
        num *= 3;
    }
}

// 判断 b 是否等于 a * 2^x * 3^y
bool is_valid(long long a, long long b) {
    if (a > b) return false;  // 边界直接返回
    for (auto x : pow2) {
        for (auto y : pow3) {
            long long res = a * x * y;
            if (res == b) return true;
            if (res > b) break;  // 剪枝：超过b直接退出
        }
    }
    return false;
}

int main() {
    precompute();

    int n;
    cin >> n;
    vector<bool> res;
    while (n--) {
        long long a, b;
        cin >> a >> b;
        res.push_back(is_valid(a, b));
    }

    // 简化输出
    for (auto i : res) cout << (i ? "Yes\n" : "No\n");
    return 0;
}