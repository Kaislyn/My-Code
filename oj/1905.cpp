#include <iostream>
#include <vector>

using namespace std;

void build_tree(vector<bool>& is_root, vector<vector<int> >& edges, int root) {
    for (int i = 0; i < edges[root].size(); i++) {
        if (!is_root[edges[root][i]]) {
            is_root[root] = true;
            // cout<<root<<" "<<i<<" "<<edges[root][i]<<is_root[root]<<endl;
            build_tree(is_root, edges, edges[root][i]);
        }
    }
}

int main() {
    int n;
    cin >> n;
    if (n == 1) {
        cout << 1 << endl;
        return 0;
    }
    int edge1, edge2;
    vector<vector<int> > edges(n + 1);
    for (int i = 1; i < n; i++) {
        cin >> edge1 >> edge2;
        edges[edge1].push_back(edge2);
        edges[edge2].push_back(edge1);
    }
    vector<bool> is_root(n + 1, 0);
    is_root[1] = 1;
    build_tree(is_root, edges, 1);
    int count = 0;
    for (int i = 1; i <= n; i++) {
        if (!is_root[i]) {
            count++;
        }
    }
    cout << count << endl;
    return 0;
}