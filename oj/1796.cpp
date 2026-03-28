#include <iostream>

using namespace std;

int num;

// (x,y)当前的位置，需要记录
void go(int x, int y, int m, int n) {
    // 超出棋盘范围
    if (x > m || y > n) {
        return;
    } else if (x == m && y == n) {
        num++;
        return;
    }
    go(x + 2, y + 1, m, n);
    go(x + 1, y + 2, m, n);
}

int main() {
    int m, n;
    cin >> m >> n;
    go(1, 1, m, n);
    cout << num;
    return 0;
}