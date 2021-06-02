#include <bits/stdc++.h>
using namespace std;
const int maxn = 205;

struct Tarjan {
  vector<int> G[maxn];
  int scc, dfs_clock, top;  // scc: 强连通分量的数量
  bool instack[maxn];
  int dfn[maxn], low[maxn], belong[maxn], Stack[maxn];
  void tarjan(int u) {
    dfn[u] = low[u] = ++dfs_clock;
    instack[u] = true;
    Stack[top++] = u;
    for (auto &v : G[u]) {
      if (!dfn[v]) {
        tarjan(v);
        low[u] = min(low[u], low[v]);
      } else if (instack[v])
        low[u] = min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u]) {
      ++scc;
      int cnt = 0;
      int now;
      while (top > 0) {
        now = Stack[--top];
        instack[now] = false;
        belong[now] = u;
        ++cnt;
        if (now == u) break;
      }
    }
  }
  void solve(int n) {
    memset(instack, 0, sizeof(instack));
    memset(dfn, 0, sizeof(dfn));
    scc = dfs_clock = top = 0;
    for (int i = 0; i < n; i++) {
      if (!dfn[i]) tarjan(i);
    }
  }
} tarjan;

struct MaxMatch {
  int n, m, clk;
  vector<int> G[maxn], rG[maxn];
  int vis[maxn], ls[maxn], rs[maxn];
  void init(int n, int m) {
    this->n = n, this->m = m;
    for (int i = 0; i < n + m; i++) G[i].clear(), rG[i].clear();
    memset(rs, -1, sizeof(rs));
    memset(ls, -1, sizeof(ls));
    memset(vis, -1, sizeof(vis));
  }
  void addEdge(int u, int v) {
    G[u].push_back(v);
    rG[v].push_back(u);
  }
  bool dfs(int u) {
    for (auto &v : G[u]) {
      if (vis[v] == clk) continue;
      vis[v] = clk;
      if (rs[v] == -1 || dfs(rs[v])) {
        ls[u] = v;
        rs[v] = u;
        return true;
      }
    }
    return false;
  }
  int match() {
    int ret = 0;
    for (clk = 0; clk < n; clk++)
      if (dfs(clk)) ++ret;
    return ret;
  }
  // ---------------------------------------
  bool lskp[maxn], rskp[maxn];
  void dfs_kp_ls(int u) {
    vis[u] = 1;
    for (auto &v : G[u]) {
      if (rs[v] == -1 || vis[rs[v]]) continue;
      dfs_kp_ls(rs[v]);
    }
  }
  void dfs_kp_rs(int u) {
    vis[u] = 1;
    for (auto &v : rG[u]) {
      if (ls[v] == -1 || vis[ls[v]]) continue;
      dfs_kp_rs(ls[v]);
    }
  }
  // O(n+m)
  int findKeyPoint() {
    // match();
    memset(lskp, 0, sizeof(lskp));
    memset(rskp, 0, sizeof(rskp));

    memset(vis, 0, sizeof(vis));
    int ret = 0;
    for (int i = 0; i < n; i++)
      if (ls[i] == -1) dfs_kp_ls(i);
    for (int i = 0; i < n; i++)
      if (!vis[i]) lskp[i] = 1, ret++;

    memset(vis, 0, sizeof(vis));
    for (int i = 0; i < m; i++)
      if (rs[i] == -1) dfs_kp_rs(i);
    for (int i = 0; i < m; i++)
      if (!vis[i]) rskp[i] = 1, ret++;

    return ret;
  }
  // -----------------------------------------
  vector<pair<int, int>> edges;
  bool ke[maxn];
  int findKeyEdge() {
    findKeyPoint();
    memset(ke, 0, sizeof(ke));
    for (int i = 0; i < n + m; i++) tarjan.G[i].clear();
    for (auto &e : edges) {
      if (ls[e.first] == e.second) {
        tarjan.G[e.first].push_back(e.second + n);
      } else {
        tarjan.G[e.second + n].push_back(e.first);
      }
    }
    tarjan.solve(n + m);
    int ret = 0;
    for (int i = 0; i < edges.size(); i++) {
      auto e = edges[i];
      if (ls[e.first] != e.second) continue;
      if (!lskp[e.first] || !rskp[e.second]) continue;
      if (tarjan.belong[e.first] != tarjan.belong[e.second + n]) {
        ke[i] = 1;
        ret++;
        continue;
      }
    }
    return ret;
  }
} bio;

int n, m, k;

int main() {
  int kase = 1;
  while (~scanf("%d%d%d", &n, &m, &k)) {
    bio.init(n, m);
    bio.edges.clear();
    for (int i = 0, u, v; i < k; i++) {
      scanf("%d%d", &u, &v);
      u--, v--;
      bio.edges.push_back({u, v});
      bio.addEdge(u, v);
    }
    int num = bio.match();
    int ans = bio.findKeyEdge();
    printf("Board %d have %d important blanks for %d chessmen.\n", kase++, ans,
           num);
  }
}