#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 5;
struct DomiTree {
  int dfs_clock;
  int dfn[maxn], id[maxn], fa[maxn];
  int semi[maxn], best[maxn], idom[maxn];
  vector<int> pre[maxn], dom[maxn], suc[maxn], son[maxn];

  void init(int n) {
    for (int i = 0; i <= n; i++) {
      pre[i].clear(), dom[i].clear(), suc[i].clear(), son[i].clear();
      fa[i] = best[i] = idom[i] = semi[i] = i, dfn[i] = 0;
    }
    dfs_clock = 0;
  }
  void addedge(int u, int v) {
    // u -> v
    pre[v].push_back(u);
    suc[u].push_back(v);
  }
  void build(int s) {
    dfs(s);
    tarjan();
  }
  void dfs(int u) {
    dfn[u] = ++dfs_clock;
    id[dfs_clock] = u;
    for (auto &v : suc[u]) {
      if (dfn[v]) continue;
      dfs(v);
      son[u].push_back(v);
    }
  }
  inline int Min(int x, int y) { return dfn[semi[x]] < dfn[semi[y]] ? x : y; }

  int find(int u) {
    if (u == fa[u]) return u;
    int v = find(fa[u]);
    best[u] = Min(best[fa[u]], best[u]);
    return fa[u] = v;
  }
  void tarjan() {
    for (int i = dfs_clock; i > 0; i--) {
      int k = id[i];
      for (auto v : pre[k]) {
        if (dfn[v] == 0) continue;
        if (dfn[v] < dfn[k] && dfn[v] < dfn[semi[k]]) semi[k] = v;
        if (dfn[v] >= dfn[k]) {
          find(v);
          semi[k] = semi[Min(best[v], k)];
        }
      }
      if (k != semi[k]) dom[semi[k]].push_back(k);
      for (auto &v : dom[k]) {
        find(v);
        if (semi[best[v]] == k)
          idom[v] = k;
        else
          idom[v] = best[v];
      }
      dom[k].clear();
      for (auto &v : son[k]) fa[v] = k;
    }
    for (int i = 2; i <= dfs_clock; i++) {
      int k = id[i];
      if (idom[k] != semi[k]) idom[k] = idom[idom[k]];
      if (k != idom[k]) dom[idom[k]].push_back(k);
    }
  }
} dt;

int ans[maxn];
void dfs(int u, int hei) {
  ans[u] = hei;
  for (auto &v : dt.dom[u]) dfs(v, hei + 1);
}

int main() {
  int n, m;
  while (~scanf("%d%d", &n, &m)) {
    dt.init(n);
    for (int i = 0; i <= n; i++) ans[i] = n;  // sb
    for (int i = 0, u, v; i < m; i++) {
      scanf("%d%d", &u, &v);
      dt.addedge(u, v);
    }
    int S, T;
    scanf("%d%d", &S, &T);
    dt.build(S);
    dfs(S, 1);
    printf("%d\n", ans[T]);
  }
}