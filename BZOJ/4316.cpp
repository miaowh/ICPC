#include <bits/stdc++.h>
using namespace std;
const int maxn = 5e4 + 5;
vector<int> G[maxn];
int par[maxn], dfn[maxn], low[maxn];
int clk;
int dp[maxn][2];

void gao(int u, int v) {}
void dfs(int u, int fa) {
  par[u] = fa;
  dfn[u] = low[u] = ++clk;
  dp[u][0] = 0, dp[u][1] = 1;
  for (auto &v : G[u]) {
    if (!dfn[v]) {
      dfs(v, u);
      low[u] = min(low[u], low[v]);
    } else if (v != fa)
      low[u] = min(low[u], dfn[v]);
    if (low[v] > dfn[u])
      dp[u][1] += dp[v][0], dp[u][0] += max(dp[v][0], dp[v][1]);
  }
  for (auto &v : G[u])
    if (par[v] != u && dfn[u] < dfn[v]) gao(u, v);
}
int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0, u, v; i < m; i++) {
    scanf("%d%d", &u, &v);
    G[u].push_back(v);
    G[v].push_back(u);
  }
}