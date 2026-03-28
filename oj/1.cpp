#include <cstring>
#include <iostream>
#include <queue>

using namespace std;

const int N = 55;
int n, m;
int grid[N][N];  // 0:ok 1:wall
int vis[N][N];
int dist[N][N];