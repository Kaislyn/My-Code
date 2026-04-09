// 经典的迷宫问题

#include <iostream>
#include <vector>

using namespace std;

// 方向向量，上、下、左、右
int dx[] = {0, 0, -1, 1}, dy[] = {1, -1, 0, 0};
vector<vector<int>> map;
vector<vector<int>> mark;
int n, m;
int num = 0;

void walk(int x, int y) {
    if (x == n - 1 && y == m - 1) {
        num++;
        return;
    }
    for (int i = 0; i < 4; i++) {
        int newx = x + dx[i];
        int newy = y + dy[i];
        // 判断是否越界
        if (newx < 0 || newy < 0 || newx >= n || newy >= m) continue;
        // 判断是否是墙，或者是否已经走过
        if (map[newx][newy] == 1 || mark[newx][newy] == 1) continue;
        mark[newx][newy] = 1;
        walk(newx, newy);
        mark[newx][newy] = 0;
    }
}

int main() {
    cin >> n >> m;
    map.resize(n, vector<int>(m, 0));
    mark.resize(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> map[i][j];
        }
    }
    mark[0][0] = 1;
    walk(0, 0);
    cout << num << endl;
    return 0;
}