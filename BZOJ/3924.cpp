#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 5;
using ll = long long;
using pii = pair<int, int>;
ll a[maxn], b[maxn], c[maxn];
int sz[maxn], heavySonSz[maxn], rt, treeSz;
bool vis[maxn];
vector<pii> G[maxn], dft[maxn];
int par[maxn];

struct LCA {
  vector<int> sp;
  int dep[maxn], dfn[maxn];
  pii dp[21][maxn << 1];

  void dfs(int u, int fa, int w) {
    dep[u] = dep[fa] + w;
    dfn[u] = sp.size();
    sp.push_back(u);
    for (auto& [v, w] : G[u]) {
      if (v == fa) continue;
      dfs(v, u, w);
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
  int dis(int u, int v) { return dep[u] + dep[v] - dep[lca(u, v)] * 2; }
} lca;

void getRoot(int u, int fa) {
  sz[u] = 1, heavySonSz[u] = 0;
  for (auto& [v, w] : G[u]) {
    if (vis[v] || v == fa) continue;
    getRoot(v, u);
    sz[u] += sz[v];
    heavySonSz[u] = max(heavySonSz[u], sz[v]);
  }
  heavySonSz[u] = max(heavySonSz[u], treeSz - sz[u]);
  if (heavySonSz[u] < heavySonSz[rt]) rt = u;
}
void build(int u) {
  vis[u] = 1;
  for (auto& [v, w] : G[u]) {
    if (vis[v]) continue;
    treeSz = sz[v], rt = 0;
    getRoot(v, u);
    par[rt] = u;
    dft[u].push_back(make_pair(v, rt));
    build(rt);
  }
}
void update(int u, int w) {
  a[u] += w;
  for (int v = u; par[v]; v = par[v]) {
    a[par[v]] += w;
    b[v] += 1LL * lca.dis(par[v], u) * w;
    c[par[v]] += 1LL * lca.dis(par[v], u) * w;
  }
}

ll count(int u) {
  ll ret = c[u];
  for (int v = u; par[v]; v = par[v]) {
    ret += c[par[v]] - b[v] + 1LL * (a[par[v]] - a[v]) * lca.dis(u, par[v]);
  }
  return ret;
}
ll query(int u) {
  ll ret = count(u);
  for (auto& [v, vrt] : dft[u]) {
    if (ret > count(v)) return query(vrt);
  }
  return ret;
}

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 1, u, v, w; i < n; i++) {
    scanf("%d%d%d", &u, &v, &w);
    G[u].push_back(make_pair(v, w));
    G[v].push_back(make_pair(u, w));
  }
  lca.dfs(1, 0, 0);
  lca.initRmq();
  rt = 0, heavySonSz[rt] = 1e9, treeSz = n;
  getRoot(1, 0);
  int RT = rt;
  par[RT] = 0;
  build(RT);

  while (m--) {
    int u, w;
    scanf("%d%d", &u, &w);
    update(u, w);
    printf("%lld\n", query(RT));
  }
}