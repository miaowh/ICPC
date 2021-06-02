#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 1e2 + 5;
const int INF = 0x3f3f3f3f;
struct Edge {
  int u, v, w;
};
struct MDST {
  vector<Edge> edges;
  int vis[maxn], id[maxn];
  int pre[maxn], val[maxn];

  void init() { edges.clear(); }
  void addEdge(int u, int v, int w) { edges.push_back({u, v, w}); }
  int zhuliu(int n, int rt) {
    int ans = 0;
    for (;;) {
      for (int i = 1; i <= n; i++) val[i] = INF, vis[i] = id[i] = 0;
      val[rt] = 0;
      for (auto &e : edges)
        if (e.u != e.v && e.w < val[e.v]) pre[e.v] = e.u, val[e.v] = e.w;
      int cnt = 0;
      for (int i = 1; i <= n; i++) {
        if (i == rt) continue;
        if (val[i] == INF) return -1;
        ans += val[i];
        int u = i;
        while (vis[u] != i && !id[u] && u != rt) {
          vis[u] = i;
          u = pre[u];
        }
        if (!id[u] && u != rt) {
          id[u] = ++cnt;
          for (int v = pre[u]; v != u; v = pre[v]) id[v] = cnt;
        }
      }
      if (!cnt) break;
      for (int i = 1; i <= n; i++)
        if (!id[i]) id[i] = ++cnt;
      for (auto &e : edges) {
        if (id[e.u] != id[e.v]) e.w -= val[e.v];
        e.u = id[e.u], e.v = id[e.v];
      }
      rt = id[rt];
      n = cnt;
    }
    return ans;
  }
} mdst;

int main() {
  int n, m, r;
  scanf("%d%d%d", &n, &m, &r);
  for (int i = 0, u, v, w; i < m; i++) {
    scanf("%d%d%d", &u, &v, &w);
    mdst.addEdge(u, v, w);
  }
  printf("%d\n", mdst.zhuliu(n, r));
}