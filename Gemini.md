# 搜索题 12 道核心模板题全集（含最优代码与核心优化）

## 🟢 第一阶段：基础搜索与回溯（必拿分模板）

### 1️⃣ 全排列（DFS 基础模板）
**题目描述**：给定 $n$ 个不同整数，输出它们的所有排列。
**思路解析**：

经典的回溯思想。将寻找排列看作在树上往下走，`used[]` 数组是“备忘录”，记录当前路径哪些数字已用。到底部时收集结果，核心在于**回溯时的“恢复现场”**。
**复杂度**：时间 $O(n \times n!)$，空间 $O(n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> nums, path;
bool used[10];

void dfs() {
    if(path.size() == n) {
        for(int v : path) cout << v << " ";
        cout << "\n";
        return;
    }
    for(int i = 0; i < n; i++){
        if(!used[i]){
            used[i] = true;
            path.push_back(nums[i]);
            dfs();
            path.pop_back(); // 回溯：恢复现场
            used[i] = false; // 回溯：恢复现场
        }
    }
}

int main(){
    cin >> n;
    nums.resize(n);
    for(int i = 0; i < n; i++) cin >> nums[i];
    dfs();
    return 0;
}
```

### 2️⃣ 最短路径（BFS 基础模板）
**题目描述**：$n \times m$ 迷宫，`.` 可走，`#` 障碍，从起点到终点最少步数。
**思路解析**：

最短路首选 BFS，像水波纹一样向外扩散，先到达的一定是最短的。`dist[][]` 兼顾了“记录步数”和“判重”两个功能。
**复杂度**：时间 $O(n \times m)$，空间 $O(n \times m)$。

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, m;
char g[20][20];
int dist[20][20];
int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};

int main(){
    cin >> n >> m;
    for(int i = 0; i < n; i++) cin >> g[i];
    memset(dist, -1, sizeof(dist));
    
    queue<pair<int,int>> q;
    q.push({0, 0});
    dist[0][0] = 0;
    
    while(!q.empty()){
        auto [x, y] = q.front(); 
        q.pop();
        
        for(int i = 0; i < 4; i++){
            int nx = x + dx[i], ny = y + dy[i];
            if(nx >= 0 && nx < n && ny >= 0 && ny < m && g[nx][ny] == '.' && dist[nx][ny] == -1){
                dist[nx][ny] = dist[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }
    cout << dist[n-1][m-1] << "\n";
    return 0;
}
```

### 3️⃣ 子集问题（DFS 选与不选模型）
**题目描述**：输出 `{1,2,3}` 的所有子集。
**思路解析**：面对每一个元素，只有“选”或“不选”两个平行分支，构成二叉搜索树。

```cpp
#include <bits/stdc++.h>
using namespace std;

vector<int> nums = {1, 2, 3}, path;

void dfs(int idx){
    if(idx == nums.size()){
        for(int x : path) cout << x << " ";
        cout << "\n";
        return;
    }
    dfs(idx + 1); // 分支 1：不选当前元素
    
    path.push_back(nums[idx]);
    dfs(idx + 1); // 分支 2：选当前元素
    path.pop_back(); // 回溯
}

int main(){
    dfs(0);
    return 0;
}
```

### 4️⃣ 八皇后（多维度状态标记）
**题目描述**：求 $n$ 皇后方案数。
**思路解析**：

用一维数组标记列。主对角线 `r - c` 为定值（加 $n$ 防负数），副对角线 `r + c` 为定值，实现 $O(1)$ 冲突检测。

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, ans = 0;
bool col[20], diag1[40], diag2[40];

void dfs(int r){
    if(r == n){ ans++; return; }
    for(int c = 0; c < n; c++){
        if(!col[c] && !diag1[r+c] && !diag2[r-c+n]){
            col[c] = diag1[r+c] = diag2[r-c+n] = true;
            dfs(r + 1);
            col[c] = diag1[r+c] = diag2[r-c+n] = false;
        }
    }
}

int main(){
    cin >> n;
    dfs(0);
    cout << ans << "\n";
    return 0;
}
```

---

## 🟡 第二阶段：进阶回溯与连通性（拉分关键）

### 5️⃣ 电话号码字母组合（多叉树回溯）
**题目描述**：数字字符串映射到字母，输出所有组合。
**思路解析**：多个独立集合的组合，当前数字决定了下一层可以展开的字母分支。

```cpp
#include <bits/stdc++.h>
using namespace std;

string digits, path;
vector<string> mapping = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};

void dfs(int idx){
    if(idx == digits.size()){ cout << path << "\n"; return; }
    for(char c : mapping[digits[idx]-'0']){
        path.push_back(c);
        dfs(idx + 1);
        path.pop_back();
    }
}

int main(){
    cin >> digits;
    if(!digits.empty()) dfs(0);
    return 0;
}
```

### 6️⃣ 状态压缩搜索（开关问题 最少步数版）
**题目描述**：$n$ 个开关，初始全关，每次翻转一个开关，求全部打开的最少步数。
**思路解析**：将开关状态压缩为整数，利用异或 `^` 翻转状态。结合 BFS 寻找最少操作步数。

```cpp
#include <bits/stdc++.h>
using namespace std;

int n;
int dist[1<<20]; // 记录到达某状态的最少步数

int bfs() {
    memset(dist, -1, sizeof(dist));
    queue<int> q;
    
    q.push(0); // 初始全 0
    dist[0] = 0;
    int target = (1 << n) - 1; // 目标全 1
    
    while(!q.empty()){
        int state = q.front(); q.pop();
        if(state == target) return dist[state];
        
        for(int i = 0; i < n; i++){
            int next_state = state ^ (1 << i); // 翻转第 i 位
            if(dist[next_state] == -1){
                dist[next_state] = dist[state] + 1;
                q.push(next_state);
            }
        }
    }
    return -1;
}

int main(){
    cin >> n;
    int ans = bfs();
    if(ans != -1) cout << "YES " << ans << "\n";
    else cout << "NO\n";
    return 0;
}
```

### 7️⃣ 连通块计数（Flood Fill 算法）
**题目描述**：二进制矩阵 1 土地，0 水，求岛屿数量。
**思路解析**：

遍历矩阵，遇到未访问的 '1'，计数器加一，并启动 DFS 把相连的 '1' 全部染色标记。

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, m;
char g[20][20];
bool vis[20][20];
int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};

void dfs(int x, int y){
    vis[x][y] = true;
    for(int i = 0; i < 4; i++){
        int nx = x + dx[i], ny = y + dy[i];
        if(nx >= 0 && nx < n && ny >= 0 && ny < m && g[nx][ny] == '1' && !vis[nx][ny])
            dfs(nx, ny);
    }
}

int main(){
    cin >> n >> m;
    for(int i = 0; i < n; i++) cin >> g[i];
    int cnt = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(g[i][j] == '1' && !vis[i][j]){
                cnt++;
                dfs(i, j);
            }
        }
    }
    cout << cnt << "\n";
    return 0;
}
```

---

## 🔴 第三阶段：强力剪枝与记忆化（防 TLE 杀手锏）

### 8️⃣ 迷宫最少步数（DFS + 记忆化最优性剪枝）
**题目描述**：迷宫求起点到终点最少步数（强制要求 DFS 写法）。
**思路解析**：DFS 走迷宫极易超时。必须引入 `memo[x][y]` 记录到达该点的历史最小步数。如果当前步数大于等于历史记录，直接剪枝废弃。

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, ans = INT_MAX;
char g[10][10];
bool vis[10][10];
int memo[10][10]; // 记忆化数组
int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};

void dfs(int x, int y, int step){
    // 强力剪枝：当前步数已经比到达该点的历史最优记录差，或比已知全局答案差
    if(step >= ans || step >= memo[x][y]) return; 
    
    memo[x][y] = step; // 更新到达该点的最优步数
    
    if(x == n-1 && y == n-1){ ans = step; return; }
    
    for(int i = 0; i < 4; i++){
        int nx = x + dx[i], ny = y + dy[i];
        if(nx >= 0 && nx < n && ny >= 0 && ny < n && g[nx][ny] == '.' && !vis[nx][ny]){
            vis[nx][ny] = true;
            dfs(nx, ny, step + 1);
            vis[nx][ny] = false;
        }
    }
}

int main(){
    cin >> n;
    for(int i = 0; i < n; i++) cin >> g[i];
    for(int i = 0; i < n; i++) fill(memo[i], memo[i]+n, INT_MAX); // 初始化
    
    vis[0][0] = true;
    dfs(0, 0, 0);
    cout << ans << "\n";
    return 0;
}
```

### 9️⃣ 所有最短路径（BFS 探路 + DFS 收集）
**题目描述**：迷宫，求起点到终点所有最短路径。
**思路解析**：先 BFS 算出每个点到起点的最短距离 `dist`，DFS 寻找路径时严格要求 `dist[nx][ny] == step + 1`，只走“下坡路”，零废动作。

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, m;
char g[10][10];
int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};
int minStep;
vector<pair<int,int>> path;
int dist[10][10];

bool inRange(int x, int y){ return x >= 0 && x < n && y >= 0 && y < m; }

void bfs(){
    memset(dist, -1, sizeof(dist));
    queue<pair<int,int>> q;
    q.push({0, 0});
    dist[0][0] = 0;
    while(!q.empty()){
        auto [x, y] = q.front(); q.pop();
        for(int i = 0; i < 4; i++){
            int nx = x + dx[i], ny = y + dy[i];
            if(inRange(nx, ny) && g[nx][ny] == '.' && dist[nx][ny] == -1){
                dist[nx][ny] = dist[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }
    minStep = dist[n-1][m-1];
}

void dfs(int x, int y, int step){
    path.push_back({x, y});
    if(x == n-1 && y == m-1){
        if(step == minStep){
            for(auto &p : path) cout << "(" << p.first << "," << p.second << ") ";
            cout << "\n";
        }
        path.pop_back();
        return;
    }
    if(step >= minStep){ path.pop_back(); return; }
    
    for(int i = 0; i < 4; i++){
        int nx = x + dx[i], ny = y + dy[i];
        // 核心剪枝：只走最短路等高线
        if(inRange(nx, ny) && g[nx][ny] == '.' && dist[nx][ny] == step + 1){
            dfs(nx, ny, step + 1);
        }
    }
    path.pop_back();
}

int main(){
    cin >> n >> m;
    for(int i = 0; i < n; i++) cin >> g[i];
    bfs();
    if(minStep != -1) dfs(0, 0, 0);
    return 0;
}
```

### 10️⃣ 拼数字方阵（DFS + 排序剪枝）
**题目描述**：填入 $n^2$ 个数字，每行每列和相等。
**思路解析**：核心优化是对输入数组进行**降序排序**，优先填大数字，极大减少搜索树的分支数。

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, targetSum, ans = 0;
vector<int> nums;
int colSum[5];
bool used[20];

void dfs(int row, int col, int sumRow){
    if(row == n){ ans++; return; }
    if(col == n){
        if(sumRow == targetSum) dfs(row + 1, 0, 0);
        return;
    }
    for(int i = 0; i < nums.size(); i++){
        // 相同数字去重剪枝 (需确保已排序)
        if(i > 0 && nums[i] == nums[i-1] && !used[i-1]) continue; 
        
        if(!used[i] && colSum[col] + nums[i] <= targetSum && sumRow + nums[i] <= targetSum){
            used[i] = true;
            colSum[col] += nums[i];
            
            dfs(row, col + 1, sumRow + nums[i]);
            
            colSum[col] -= nums[i];
            used[i] = false;
        }
    }
}

int main(){
    cin >> n;
    nums.resize(n * n);
    int sumAll = 0;
    for(int i = 0; i < n * n; i++){ cin >> nums[i]; sumAll += nums[i]; }
    
    if(sumAll % n != 0){ cout << 0; return 0; }
    targetSum = sumAll / n;
    
    // 关键优化：降序排序，优先大数字填坑
    sort(nums.rbegin(), nums.rend()); 
    
    memset(colSum, 0, sizeof(colSum));
    memset(used, 0, sizeof(used));
    dfs(0, 0, 0);
    cout << ans << "\n";
    return 0;
}
```

### 11️⃣ 最少硬币凑数（记忆化搜索 / 动态规划）
**题目描述**：$n$ 种硬币（可重复），金额 $m$，求最少硬币数。
**思路解析**：纯 DFS 会爆栈超时。引入 `memo` 数组记录凑出某个金额的最少硬币数，将复杂度从指数级降为 $O(n \times m)$。

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<int> coins;
int memo[10005]; // 记忆化数组

int dfs(int sum) {
    if(sum > m) return 1e9; // 无效状态
    if(sum == m) return 0;  // 达成目标，需要 0 个额外硬币
    if(memo[sum] != -1) return memo[sum]; // 命中缓存
    
    int min_coins = 1e9;
    for(int i = 0; i < n; i++) {
        min_coins = min(min_coins, dfs(sum + coins[i]) + 1);
    }
    return memo[sum] = min_coins; // 存入缓存
}

int main(){
    cin >> n >> m;
    coins.resize(n);
    for(int i = 0; i < n; i++) cin >> coins[i];
    
    memset(memo, -1, sizeof(memo));
    int ans = dfs(0);
    
    if(ans >= 1e9) cout << -1 << "\n";
    else cout << ans << "\n";
    return 0;
}
```

### 12️⃣ 打印迷宫最长路径（DFS 纯暴搜）
**题目描述**：求起点到终点的最长可走路径长度（不重复走）。
**思路解析**：NP-Hard 问题，无法像最短路那样轻易剪枝。只能靠 DFS 老老实实回溯。确保 `vis = true` 后必须撤销为 `false`。

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, m, ans = 0;
char g[10][10];
bool vis[10][10];
int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};

bool inRange(int x, int y){ return x >= 0 && x < n && y >= 0 && y < m; }

void dfs(int x, int y, int step){
    if(x == n-1 && y == m-1) {
        ans = max(ans, step);
        // 注意：找最长路这里不需要 return，因为可能绕一圈再到终点
        // 但题目如果是“到终点就停止”，则加上 return
    }
    
    for(int i = 0; i < 4; i++){
        int nx = x + dx[i], ny = y + dy[i];
        if(inRange(nx, ny) && g[nx][ny] == '.' && !vis[nx][ny]){
            vis[nx][ny] = true;
            dfs(nx, ny, step + 1);
            vis[nx][ny] = false; // 必须回溯
        }
    }
}

int main(){
    cin >> n >> m;
    for(int i = 0; i < n; i++) cin >> g[i];
    vis[0][0] = true;
    dfs(0, 0, 0);
    cout << ans << "\n";
    return 0;
}
```

---
