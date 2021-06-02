#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 5;

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
typedef pair<int, int> pii;

struct LCA {
  vector<int> sp;
  int dep[maxn], dfn[maxn];
  pii dp[21][maxn << 1];
  void init(int n) { sp.clear(); }
  void dfs(int u, int fa) {
    dep[u] = dep[fa] + 1;
    dfn[u] = sp.size();
    sp.push_back(u);
    for (auto &v : dt.dom[u]) {
      if (v == fa) continue;
      dfs(v, u);
      sp.push_back(u);
    }
  }
  void initRmq() {
    int n = sp.size();
    for (int i = 0; i < n; i++) dp[0][i] = {dfn[sp[i]], sp[i]};
    for (int i = 1; (1 << i) <= n; i++)
      for (int j = 0; j + (1 << i) - 1 < n; j++)
        dp[i][j] = min(dp[i - 1][j], dp[i - 1][j + (1 << (i - 1))]);
  }
  int lca(int u, int v) {
    int l = dfn[u], r = dfn[v];
    if (l > r) swap(l, r);
    int k = 31 - __builtin_clz(r - l + 1);
    return min(dp[k][l], dp[k][r - (1 << k) + 1]).second;
  }
} lca;

int in[maxn];
int dep[maxn];
void dfs(int u, int h) {
  dep[u] = h;
  for (auto &v : dt.dom[u]) {
    dfs(v, h + 1);
  }
}
int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int n, m, rt;
    scanf("%d%d", &n, &m);
    rt = ++n;
    for (int i = 0; i <= n; i++) in[i] = 0;
    dt.init(n);
    lca.init(n);
    for (int i = 0, u, v; i < m; i++) {
      scanf("%d%d", &u, &v);
      dt.addedge(v, u);
      in[u]++;
    }
    for (int i = 1; i < n; i++)
      if (in[i] == 0) dt.addedge(rt, i);
    dt.build(rt);
    lca.dfs(rt, 0);
    lca.initRmq();
    dfs(rt, 0);

    int q, a, b;
    scanf("%d", &q);
    while (q--) {
      scanf("%d%d", &a, &b);
      int fa = lca.lca(a, b);
      printf("%d\n", dep[a] + dep[b] - dep[fa]);
    }
  }
}
