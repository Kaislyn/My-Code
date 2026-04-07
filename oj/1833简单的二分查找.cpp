#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    long long start, end, target;
    cin >> start >> end >> target;
    long long middle = 0;
    while (middle != target) {
        middle = (start + end) / 2;
        if (middle < target) {
            start = middle + 1;
            cout << 'R';
        } else if (middle > target) {
            end = middle - 1;
            cout << 'L';
        } else {
            cout << 'G';
        }
    }
    return 0;
}
