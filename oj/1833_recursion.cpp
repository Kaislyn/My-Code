// 递归写法

#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

void binary_search(ll left, ll right, ll target) {
    ll middle = (left + right) / 2;
    if (middle == target) {
        cout << "G";
        return;
    } else if (middle > target) {
        cout << "L";
        binary_search(left, middle - 1, target);
    } else if (middle < target) {
        cout << "R";
        binary_search(middle + 1, right, target);
    }
}

int main() {
    ll left, right, target;
    cin >> left >> right >> target;
    binary_search(left, right, target);
    return 0;
}