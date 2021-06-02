#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
const int maxn = 1e5 + 5;
vector<int> G[maxn], dft[maxn];
int sz[maxn], heavySonSz[maxn], treeSz, rt, par[maxn], ans;
int stat[maxn];
bool vis[maxn], tag[maxn];
multiset<int, greater<int> > a[maxn], b[maxn], c;

struct LCA {
  vector<int> sp;
  int dep[maxn], dfn[maxn];
  pii dp[21][maxn << 1];
  void dfs(int u, int fa) {
    dep[u] = dep[fa] + 1;
    dfn[u] = sp.size();
    sp.push_back(u);
    for (int i = 0; i < G[u].size(); i++) {
      int v = G[u][i];
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
  int dis(int u, int v) {
    int p = lca(u, v);
    return dep[u] + dep[v] - 2 * dep[p];
  }
} lca;

void findRoot(int u, int fa) {
  sz[u] = 1, heavySonSz[u] = 0;
  for (int i = 0; i < G[u].size(); i++) {
    int v = G[u][i];
    if (vis[v] || v == fa) continue;
    findRoot(v, u);
    sz[u] += sz[v];
    heavySonSz[u] = max(heavySonSz[u], sz[v]);
  }
  heavySonSz[u] = max(heavySonSz[u], treeSz - sz[u]);
  if (heavySonSz[u] < heavySonSz[rt]) rt = u;
}
void build(int u) {
  vis[u] = 1;
  for (int i = 0; i < G[u].size(); i++) {
    int v = G[u][i];
    if (vis[v]) continue;
    rt = 0, treeSz = sz[v];
    findRoot(v, u);
    dft[u].push_back(rt);
    dft[rt].push_back(u);
    par[rt] = u;
    build(rt);
  }
}

int get2ele(int u) {
  int ret = 0, cnt = 0;
  for (set<int>::iterator it = b[u].begin(); it != b[u].end(); it++) {
    if (cnt == 2) break;
    ret += *it;
    cnt++;
  }
  return ret;
}
void gao(int u, int p) {
  a[p].insert(lca.dis(par[p], u));
  for (int i = 0; i < dft[u].size(); i++) {
    int v = dft[u][i];
    if (v == par[u]) continue;
    gao(v, p);
  }
}
void solve(int u) {
  if (par[u] != u) gao(u, u);
  b[u].insert(0);
  for (int i = 0; i < dft[u].size(); i++) {
    int v = dft[u][i];
    if (v == par[u]) continue;
    solve(v);
    b[u].insert(*a[v].begin());
  }
  if (b[u].size() > 1) c.insert(get2ele(u));
}

void setTag(int u) {
  if (par[u] == u) return;
  tag[u] = 1;
  setTag(par[u]);
}

void turnOff(int u, int p) {
  int v = -1;
  for (int i = 0; i < dft[u].size(); i++) {
    int x = dft[u][i];
    if (x == par[u]) continue;
    if (tag[x]) {
      v = x;
      tag[x] = 0;
      break;
    }
  }
  if (b[u].size() > 1) c.erase(c.find(get2ele(u)));
  if (par[u] != u) a[u].erase(a[u].find(lca.dis(par[u], p)));
  if (u == p) {
    b[u].erase(0);
    stat[u] ^= 1;
  } else {
    if (a[v].size()) b[u].erase(b[u].find(*a[v].begin()));
    turnOff(v, p);
    if (a[v].size()) b[u].insert(*a[v].begin());
  }
  if (b[u].size() > 1) c.insert(get2ele(u));
}

void turnOn(int u, int p) {
  int v = -1;
  for (int i = 0; i < dft[u].size(); i++) {
    int x = dft[u][i];
    if (x == par[u]) continue;
    if (tag[x]) {
      v = x;
      tag[x] = 0;
      break;
    }
  }
  if (b[u].size() > 1) c.erase(c.find(get2ele(u)));
  if (par[u] != u) a[u].insert(lca.dis(par[u], p));
  if (u == p) {
    b[u].insert(0);
    stat[u] ^= 1;
  } else {
    if (a[v].size()) b[u].erase(b[u].find(*a[v].begin()));
    turnOn(v, p);
    if (a[v].size()) b[u].insert(*a[v].begin());
  }
  if (b[u].size() > 1) c.insert(get2ele(u));
}

int main() {
  int n, m;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) stat[i] = 1;
  for (int i = 1, u, v; i < n; i++) {
    scanf("%d%d", &u, &v);
    G[u].push_back(v);
    G[v].push_back(u);
  }
  lca.dfs(1, 0);
  lca.initRmq();
  rt = 0, heavySonSz[rt] = 1e9, treeSz = n;
  findRoot(1, 0);
  int tmp = rt;
  build(rt);
  rt = tmp;
  par[rt] = rt;
  solve(rt);
  scanf("%d", &m);
  while (m--) {
    char op[2];
    int p;
    scanf("%s", op);
    if (op[0] == 'C') {
      scanf("%d", &p);
      setTag(p);
      if (stat[p] == 1)
        turnOff(rt, p);
      else
        turnOn(rt, p);
    } else {
      if (c.size())
        printf("%d\n", *c.begin());
      else if (b[rt].size())
        puts("0");
      else
        puts("-1");
    }
  }
}
/*
8
1 2
2 3
3 4
3 5
3 6
6 7
6 8
7
G
C 1
G
C 2
G
C 1
G
*/