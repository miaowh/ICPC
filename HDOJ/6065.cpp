#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
const int maxn = 3e5 + 5;
int a[maxn], sz[maxn];
vector<int> G[maxn];
struct LCA {
  vector<int> sp;
  int dep[maxn], dfn[maxn];
  pii dp[21][maxn << 1];
  void init() {
    dep[0] = 0;
    sp.clear();
  }
  void dfs(int u, int fa) {
    dep[u] = dep[fa] + 1;
    dfn[u] = sp.size();
    sp.push_back(u);
    for (auto &v : G[u]) {
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

int main() {
  int n, k;
  while (~scanf("%d%d", &n, &k)) {
    for (int i = 1; i <= n; i++) scanf("%d", a + i), G[i].clear();
    for (int i = 0, u, v; i < n - 1; i++) {
      scanf("%d%d", &u, &v);
      G[u].push_back(v);
      G[v].push_back(u);
    }
    lca.init();
    lca.dfs(1, 0);
    lca.initRmq();
    vector<int> dp[n + 1];
    for (int i = 0; i <= n; i++) dp[i].assign(k + 1, 1e9);
    dp[0][0] = 0;
    for (int i = 1; i <= n; i++) {
      dp[i][0] = 0;
      for (int j = 1; j <= k; j++) {
        dp[i][j] = min(dp[i - 1][j], dp[i - 1][j - 1] + lca.dep[a[i]]);
        if (i > 1)
          dp[i][j] = min(dp[i][j],
                         dp[i - 2][j - 1] + lca.dep[lca.lca(a[i], a[i - 1])]);
      }
    }
    printf("%d\n", dp[n][k]);
  }
}