#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

unordered_map<int, int> s;

int main() {
    // 总共有 T 组需要处理，列表大小为 n
    int T, n;
    cin >> T;
    while (T--) {
        s.clear();
        cin >> n;
        vector<int> a(n, 0), b(n, 0), c(n, 0), d(n, 0);
        for (int i = 0; i < n; i++) {
            cin >> a[i] >> b[i] >> c[i] >> d[i];
        }
        // 分两组进行相加，降低复杂度，n^4 -> n^2
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                s[a[i] + b[j]] += 1;
            }
        }
        int num = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                auto it = s.find(-(c[i] + d[j]));
                if (it != s.end()) num += it->second;
            }
        }
        cout << num << endl;
    }
    return 0;
}