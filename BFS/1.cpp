// bfs经典:迷宫问题寻找最短路径

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// 定义一个结构体，打包坐标(x, y)和走到这步的步数(step)
struct Node {
    int x, y, step;
};

int dx[] = {-1, 1, 0, 0}, dy[] = {0, 0, -1, 1};
vector<vector<int>> map;
vector<vector<int>> mark;
int n, m;

void bfs(int x, int y) {
    queue<Node> q;

    q.push({x, y, 0});
    mark[x][y] = 1;

    while (!q.empty()) {
        Node current = q.front();
        q.pop();

        if (current.x == n - 1 && current.y == m - 1) {
            cout << "最短步数是: " << current.step << endl;
            return;
        }

        // 开始探索方向
        for (int i = 0; i < 4; i++) {
            int newx = current.x + dx[i];
            int newy = current.y + dy[i];
            // 越界检查
            if (newx < 0 || newy < 0 || newx >= n || newy >= m) continue;
            // 墙壁和已访问检查
            if (map[newx][newy] == 1 || mark[newx][newy] == 1) continue;

            q.push({newx, newy, current.step + 1});
            mark[newx][newy] = 1;
        }
    }
    cout << "无法到达终点" << endl;
}

int main() {
    cin >> n >> m;
    bfs(0, 0);
    return 0;
}