#include <iostream>
#include <vector>

using namespace std;

int n, k, x, y, h;
vector<vector<int>> map;  // 1代表将的位置，-1代表将的看守位置，0代表普通位置
vector<int> ans;
int dx[] = {0, 0, -1, 1};
int dy[] = {-1, 1, 0, 0};
int num = 1;

void dfs(int x, int y) {
    if (h > 0) {
        num++;
    }
    if (h == 0) {
        ans.push_back(num);
        return;
    }
    for (int i = 0; i < 4; i++) {
        int newx = x + dx[i];
        int newy = y + dy[i];
        if (newx < 1 || newy < 1 || newx > n || newy > n) continue;
        if (map[newx][newy] == 1) continue;
        if (map[newx][newy] == -1) {
            h--;
            dfs(newx, newy);
            num--;
            h++;
        } else {
            dfs(newx, newy);
            num--;
        }
    }
}

int main() {
    // 地图的尺寸，将的个数，出生点的行号和列号，初始的血量
    cin >> n >> k >> x >> y >> h;
    map.resize(n + 1, vector<int>(n + 1, 0));
    int k_x, k_y;
    while (k--) {
        cin >> k_x >> k_y;
        map[k_x][k_y] = 1;
        // 标记将的看守位置
        for (int i = 0; i < 4; i++) {
            int newx = k_x + dx[i];
            int newy = k_y + dy[i];
            // 越界检查
            if (newx < 1 || newy < 1 || newx > n || newy > n) continue;
            map[newx][newy] = -1;
        }
    }

    // for(int i=1;i<=n;i++){
    //     for(int j=1;j<=n;j++){
    //         cout<<map[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }

    dfs(x, y);
    int max_ans = 0;
    for (auto& i : ans) max_ans = max(max_ans, i);
    cout << max_ans << endl;
    return 0;
}