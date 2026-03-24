#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int> > map(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < m; j++) {
            cin >> map[i][j];
        }
    }
    // 人和西瓜的横坐标和纵坐标
    int a_x, a_y, b_x, b_y;
    cin >> a_x >> a_y >> b_x >> b_y;

    return 0;
}