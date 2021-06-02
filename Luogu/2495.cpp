#include <bits/stdc++.h>
using namespace std;
const int maxn = 3e5 + 5;
const int BASE = 20;
using pii = pair<int, int>;
using ll = long long;
vector<pii> G[maxn];
int dfn[maxn], clk = 0;
int dep[maxn];
int par[maxn][BASE + 1];
int val[maxn][BASE + 1];

void dfs1(int u, int fa) {
  dfn[u] = ++clk;
  dep[u] = dep[fa] + 1;
  par[u][0] = fa;
  for (auto &V : G[u]) {
    if (V.first == fa) continue;
    val[V.first][0] = V.second;
    dfs1(V.first, u);
  }
}
void init(int n) {
  for (int j = 1; j <= BASE; j++)
    for (int i = 1; i <= n; i++) {
      int v = par[i][j - 1];
      par[i][j] = par[v][j - 1];
      val[i][j] = min(val[i][j - 1], val[v][j - 1]);
    }
}
int lca(int u, int v) {
  if (dep[u] > dep[v]) swap(u, v);
  for (int i = BASE; i >= 0; i--)
    if (dep[par[v][i]] >= dep[u]) v = par[v][i];  // 先跳到同一高度

  if (u == v) return u;
  for (int i = BASE; i >= 0; i--)
    if (par[u][i] != par[v][i]) u = par[u][i], v = par[v][i];  // 一起向上跳
  return par[u][0];
}

// ----------------------
int stk[maxn], top;
vector<int> g[maxn];
void clean(int u) {
  for (auto &v : g[u]) clean(v);
  g[u].clear();
}
inline void addEdge(int u, int v) { g[u].push_back(v); }
void build(vector<int> &ps) {
  clean(1);
  sort(ps.begin(), ps.end(),
       [&](const int &a, const int &b) { return dfn[a] < dfn[b]; });
  stk[top = 1] = 1;
  for (auto &u : ps) {
    if (u == 1) continue;
    int fa = lca(u, stk[top]);
    if (fa != stk[top]) {
      while (dfn[fa] < dfn[stk[top - 1]]) {
        addEdge(stk[top - 1], stk[top]);
        --top;
      }
      addEdge(fa, stk[top--]);
      if (dfn[fa] > dfn[stk[top]]) stk[++top] = fa;
    }
    stk[++top] = u;
  }
  for (int i = 1; i < top; i++) addEdge(stk[i], stk[i + 1]);
}

// ---------------------
int dist(int u, int v) {
  int ret = 1e9;
  for (int i = BASE; i >= 0; i--)
    if (par[v][i] != u) ret = min(ret, val[v][i]), v = par[v][i];  // 一起向上跳
  return min(ret, val[v][0]);
}

void debug(int u) {
  for (auto &v : g[u])
    cerr << u << " ---> " << v << "  : " << dist(u, v) << endl;
  for (auto &v : g[u]) debug(v);
}

ll dp[maxn];
bool key[maxn];
void dfs2(int u) {
  dp[u] = 0;
  for (auto &v : g[u]) {
    dfs2(v);
    int tmp = dist(u, v);
    if (key[v])
      dp[u] += tmp;
    else
      dp[u] += min(dp[v], 1LL * tmp);
  }
}
int main() {
  int n, m;
  scanf("%d", &n);
  for (int i = 0, u, v, w; i < n - 1; i++) {
    scanf("%d%d%d", &u, &v, &w);
    G[u].push_back({v, w});
    G[v].push_back({u, w});
  }
  memset(val[0], 0x3f, sizeof(val[0]));
  val[1][0] = 1e9;
  dfs1(1, 0);
  init(n);

  scanf("%d", &m);
  for (int i = 0, k; i < m; i++) {
    scanf("%d", &k);
    vector<int> ps;
    for (int j = 0, x; j < k; j++) {
      scanf("%d", &x);
      key[x] = 1;
      ps.push_back(x);
    }
    build(ps);
    // debug(1);
    dfs2(1);
    printf("%lld\n", dp[1]);
    for (auto &v : ps) key[v] = 0;
  }
}