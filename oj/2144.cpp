#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    // 字符个数以及询问次数
    int n, q;
    cin >> n >> q;
    string str;
    cin >> str;
    // 标记每个字符出现的个数
    vector<int> sign(26);
    for (auto& c : str) {
        sign[c - 'a']++;
    }
    char c;
    while (q--) {
        cin >> c;
        cout << sign[c - 'a'] << endl;
    }
    return 0;
}