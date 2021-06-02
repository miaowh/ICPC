// #include <bits/stdc++.h>
#include <algorithm>
#include <cstdio>

using namespace std;

const int INF = 0x3f3f3f3f;
const int maxn = 505;
// O(n^3)  1-index
struct StoerWagner {
  int n;
  int mask[maxn];  // 因为有删点的操作，所以用mask[i]来表示第i个位置是几号点
  int G[maxn][maxn];  // 邻接矩阵
  int d[maxn];        // 表示集合到各个点的距离
  bool vis[maxn];     // 该点是否加入了集合
  void init(int n) {
    this->n = n;
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= n; j++) G[i][j] = 0;
  }
  void addedge(int u, int v, int c) {
    G[u][v] += c;
    G[v][u] += c;
  }
  int solve() {
    int res = INF;
    for (int i = 1; i <= n; i++) mask[i] = i;
    while (n > 1) {
      int k, pre = 1;  // 默认1号点是集合的第一个点
      for (int i = 1; i <= n; i++) vis[mask[i]] = 0, d[mask[i]] = 0;
      vis[mask[pre]] = true;
      for (int i = 2; i <= n; i++) {
        k = -1;
        for (int j = 1; j <= n; j++) {  // 寻找距离最远的点加入集合
          if (!vis[mask[j]]) {
            d[mask[j]] += G[mask[pre]][mask[j]];
            if (k == -1 || d[mask[k]] < d[mask[j]]) k = j;
          }
        }
        vis[mask[k]] = true;  // 加入集合
        if (i == n) {         // 只剩一个点
          res = min(res, d[mask[k]]);
          for (int j = 1; j <= n; j++) {  // 修改边权
            G[mask[pre]][mask[j]] += G[mask[j]][mask[k]];
            G[mask[j]][mask[pre]] += G[mask[j]][mask[k]];
          }
          mask[k] = mask[n--];  // 去掉最后加入的点
        }
        pre = k;
      }
    }
    return res;
  }
} sw;

int main() {
  int n, m;
  while (~scanf("%d%d", &n, &m)) {
    sw.init(n);
    for (int i = 0, u, v, w; i < m; i++) {
      scanf("%d%d%d", &u, &v, &w);
      u++, v++;
      sw.addedge(u, v, w);
    }
    printf("%d\n", sw.solve());
  }
}