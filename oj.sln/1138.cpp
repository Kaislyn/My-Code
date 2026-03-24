// 根据二叉树的前序遍历和中序遍历，打印后序

#include <iostream>
#include <string>

using namespace std;

// 这个算法不断拆分成最小子树，每个子树都是左右根的顺序打印
// pre:根左右 in:左根右
void print(string pre, string in) {
    if (pre.empty()) return;
    char root = pre[0];
    int root_index = in.find(root);

    // 中序遍历的左子树/右子树
    string in_left = in.substr(0, root_index);
    string in_right = in.substr(root_index + 1);

    // 前序遍历的左子树和右子树
    string pre_left = pre.substr(1, in_left.size());
    string pre_right = pre.substr(in_left.size() + 1);

    print(pre_left, in_left);
    print(pre_right, in_right);
    cout << root;
}

int main() {
    string pre_order, in_order;
    cin >> pre_order >> in_order;
    print(pre_order, in_order);
    return 0;
}