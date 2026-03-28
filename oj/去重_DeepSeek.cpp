/**
 * @file unique_preserve_order.cpp
 * @brief 在不排序的情况下对序列进行去重（保留第一次出现的顺序）
 *
 * 使用方法：
 *   1. 包含 <vector>, <unordered_set> 等头文件
 *   2. 调用 unique_preserve_order 函数
 *   3. 函数返回去重后的新序列（原容器不变），或直接修改原容器
 *
 * 原理：利用哈希集合记录已经出现过的元素，遍历时若元素未出现过则保留。
 */

#include <algorithm>  // for copy, back_inserter
#include <iostream>
#include <unordered_set>
#include <vector>

/**
 * 版本1：返回去重后的新 vector（原容器不变）
 */
template <typename T>
std::vector<T> unique_preserve_order(const std::vector<T>& input) {
    std::unordered_set<T> seen;
    std::vector<T> result;
    for (const auto& val : input) {
        if (seen.find(val) == seen.end()) {  // 未出现过
            seen.insert(val);
            result.push_back(val);
        }
    }
    return result;
}

/**
 * 版本2：原地修改 vector，移除重复元素（保持原顺序）
 */
template <typename T>
void unique_preserve_order_inplace(std::vector<T>& vec) {
    std::unordered_set<T> seen;
    auto it = vec.begin();
    while (it != vec.end()) {
        if (seen.find(*it) != seen.end()) {
            it = vec.erase(it);  // 重复元素，删除并更新迭代器
        } else {
            seen.insert(*it);
            ++it;
        }
    }
}

int main() {
    // 测试数据
    std::vector<int> data = {5, 2, 8, 2, 1, 5, 3, 1, 4, 2};

    std::cout << "原始序列: ";
    for (int x : data) std::cout << x << " ";
    std::cout << std::endl;

    // 方式1：获取新容器
    auto unique_data = unique_preserve_order(data);
    std::cout << "去重后（新容器）: ";
    for (int x : unique_data) std::cout << x << " ";
    std::cout << std::endl;

    // 方式2：原地修改
    unique_preserve_order_inplace(data);
    std::cout << "去重后（原地修改）: ";
    for (int x : data) std::cout << x << " ";
    std::cout << std::endl;

    return 0;
}