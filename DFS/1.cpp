#include <iostream>
#include <vector>

using namespace std;

int n, s, sum = 0;
vector<int> ans;

void dfs(int start) {
    if (sum > s) {
        return;
    } else if (sum == s) {
        for (auto& i : ans) cout << i << ' ';
        cout << endl;
        return;
    }
    for (int i = start; i <= n; i++) {
        ans.push_back(i);
        sum += i;
        dfs(i + 1);
        ans.pop_back();
        sum -= i;
    }
}

int main() {
    cin >> n >> s;
    dfs(1);
    return 0;
}