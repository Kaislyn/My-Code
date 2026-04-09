#include <iostream>
#include <vector>

using namespace std;

int n, k;
vector<int> ans;

// start 表示当前这一层允许选择的最小数字
void dfs(int start) {
    if (ans.size() == k) {
        for (int i : ans) cout << i << " ";
        cout << "\n";
        return;
    }

    // 从 start 开始选，确保不会选之前的数字，保证升序
    for (int i = start; i <= n; i++) {
        ans.push_back(i);
        dfs(i + 1);
        ans.pop_back();
    }
}

int main() {
    cin >> n >> k;
    dfs(1);  // 初始从 1 开始选
    return 0;
}