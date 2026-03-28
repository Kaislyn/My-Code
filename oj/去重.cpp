#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> seq = {5, 2, 8, 2, 1, 5, 3, 1};

    // 1. 升序排序
    std::sort(seq.begin(), seq.end());

    // 2. 去重（移动重复元素到末尾）
    auto last = std::unique(seq.begin(), seq.end());

    // 3. 删除重复元素
    seq.erase(last, seq.end());

    // 输出结果
    for (int x : seq) {
        std::cout << x << " ";
    }
    // 输出: 1 2 3 5 8
    return 0;
}

// 还可以用<set>
/*
说明
std::sort 默认按升序排列，如需降序可传入 std::greater<>() 作为第三个参数。

std::unique 仅移除 相邻 的重复元素，因此必须先排序。

对于 std::list 等双向链表，也可直接使用其成员函数 sort() 和 unique()，效果相同。

使用 std::set 的替代方案
如果不需要保留原序列，也可以直接将序列元素插入到 std::set 中（自动排序并去重），再拷贝回原容器：

cpp
std::set<int> s(seq.begin(), seq.end());
seq.assign(s.begin(), s.end());
但这种方式会丢失重复元素的信息，且可能产生额外的拷贝开销。

根据实际场景选择合适的方法即可。
 */