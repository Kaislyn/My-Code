// 给定一个整数，输出从 1 到这个整数的所有全排列
#include <iostream>
#include <vector>

using namespace std;

int n;
vector<int> path;
vector<bool> visited;

void dfs(int step) {
    if (step > n) {
        for (auto& i : path) {
            cout << i << " ";
        }
        cout << "\n";
        return;
    }
    // 核心：挨个试1~n所有数字
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            path.push_back(i);
            visited[i] = true;
            // 递归进入下一层，找寻下一个位置可放入的数字
            dfs(step + 1);
            // 回溯，恢复原有状态
            visited[i] = false;
            path.pop_back();
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    visited.resize(n + 1, false);

    // 从第一个位置开始填数字
    dfs(1);

    return 0;
}