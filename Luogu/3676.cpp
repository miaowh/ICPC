#include <bits/stdc++.h>
using namespace std;

const int maxn = 1000000;
struct HLD {
  int n, dfn;
  int sz[maxn], top[maxn], son[maxn], dep[maxn], par[maxn], id[maxn], rk[maxn];
  vector<int> G[maxn];
  void init(int n) {
    this->n = n;
    clr(son, -1);
    dfn = 0;
    for (int i = 0; i <= n; i++) G[i].clear();
  }
  void addedge(int u, int v) {
    G[u].pb(v);
    G[v].pb(u);
  }
  void build() {
    dfs(1, 1, 1);
    link(1, 1);
  }
  void dfs(int u, int fa, int d) {
    dep[u] = d;
    par[u] = fa;
    sz[u] = 1;
    for (auto &v : G[u]) {
      if (v == fa) continue;
      dfs(v, u, d + 1);
      sz[u] += sz[v];
      if (son[u] == -1 || sz[v] > sz[son[u]]) son[u] = v;
    }
  }
  void link(int u, int t) {
    top[u] = t;
    id[u] = ++dfn;
    rk[dfn] = u;
    if (son[u] == -1) return;
    link(son[u], t);  // 保证重链的dfs序是连续的
    for (auto &v : G[u]) {
      if (v != son[u] && v != par[u]) link(v, v);
    }
  }

  void update(int u, int v, int w) {}  // 数据结构
  int query(int u, int v) {}           // 数据结构

  void update_path(int u, int v, int w) {
    while (top[u] != top[v]) {
      if (dep[top[u]] < dep[top[v]]) swap(u, v);
      update(id[top[u]], id[u], w);
      u = par[top[u]];
    }
    // if(u == v) return;   // 边权
    if (dep[u] > dep[v]) swap(u, v);
    update(id[u], id[v], w);  // 点权
                              // update(id[u] + 1,id[v],w);  // 边权
  }
  int query_path(int u, int v) {
    int ret = 0;
    while (top[u] != top[v]) {
      if (dep[top[u]] < dep[top[v]]) swap(u, v);
      ret += query(id[top[u]], id[u]);
      u = par[top[u]];
    }
    // if(u == v) return ret;   // 边权
    if (dep[u] > dep[v]) swap(u, v);
    ret += query(id[u], id[v]);  // 点权
    // ret += query(id[u] + 1,id[v]);  // 边权
    return ret;
  }
} hld;

vector<int> G[maxn];

int main() {
  int n, q;
  scanf("%d%d", &n, &q);
  for (int i = 1, u, v; i < n; i++) {
    scanf("%d%d", &u, &v);
    G[u].push_back(v);
    G[v].push_back(u);
  }
  while (q--) {
  }
}