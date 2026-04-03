#include <iostream>
#include <vector>

using namespace std;

int main() {
    // m:0,n:1
    int m, n;
    cin >> m >> n;
    vector<int> ac_m(m, 0), ac_n(n, 0);
    for (auto& i : ac_m) cin >> i;
    for (auto& j : ac_n) cin >> j;

    return 0;
}