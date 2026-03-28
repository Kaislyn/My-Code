#include <iostream>
#include <set>
#include <vector>

using namespace std;

set<int> s;

struct TreeNode {
    int val;
    vector<TreeNode*> childs;
    TreeNode(int x) : val(x), childs() {}
};

int main() {
    int num;
    cin >> num;
    // 1 -> root
    TreeNode* root = new TreeNode(1);
    s.insert(1);
    int i, j;
    while (num--) {
        cin >> i >> j;
        auto it = s.find(i);
        if (it != s.end()) {
        }
    }
    return 0;
}