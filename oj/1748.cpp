#include <iostream>
#include <vector>

using namespace std;

int main() {
    // 总共有T组需要处理，列表大小为n
    int T, n;
    cin >> T;
    while (T--) {
        cin >> n;
        vector<int> a(n, 0), b(n, 0), c(n, 0), d(n, 0);
        for (int i = 0; i < n; i++) {
            cin >> a[i] >> b[i] >> c[i] >> d[i];
        }
        }
    return 0;
}