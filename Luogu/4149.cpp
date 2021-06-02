/*
  维护每个权值的最小边数。直接multiset[x]，
  表示从根节点出发经过多少条边可以使得权值为x。
*/
#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 5;
const int maxn1 = 1e6 + 5;
using pii = pair<int, int>;
vector<pii> G[maxn];
bool vis[maxn];
multiset<int> val[maxn1];
int n, k, ans, rt, treeSz;
int sz[maxn], heavySonSz[maxn];

void findRoot(int u, int fa) {
  sz[u] = 1, heavySonSz[u] = 0;
  for (auto& [v, w] : G[u]) {
    if (vis[v] || v == fa) continue;
    findRoot(v, u);
    sz[u] += sz[v];
    heavySonSz[u] = max(heavySonSz[u], sz[v]);
  }
  heavySonSz[u] = max(heavySonSz[u], treeSz - sz[u]);
  if (heavySonSz[u] < heavySonSz[rt]) rt = u;
}

void gao(int u, int fa, int x, int edges, int sign) {
  if (x > k) return;
  if (sign == 1)
    val[x].insert(edges);
  else {
    val[x].erase(val[x].find(edges));
  }
  for (auto& [v, w] : G[u]) {
    if (vis[v] || v == fa) continue;
    gao(v, u, x + w, edges + 1, sign);
  }
}
void find(int u, int fa, int x, int edges) {
  if (x > k) return;
  if (val[k - x].size()) ans = min(ans, edges + *val[k - x].begin());
  for (auto& [v, w] : G[u]) {
    if (vis[v] || v == fa) continue;
    find(v, u, x + w, edges + 1);
  }
}
void cal(int u, int fa) {
  gao(u, fa, 0, 0, 1);
  if (val[k].size()) ans = min(ans, *val[k].begin());
  for (auto& [v, w] : G[u]) {
    if (vis[v] || v == fa) continue;
    gao(v, u, w, 1, -1);
    find(v, u, w, 1);
    gao(v, u, w, 1, 1);
  }
  gao(u, fa, 0, 0, -1);
}
void dfs(int u) {
  vis[u] = 1;
  cal(u, -1);
  for (auto& [v, w] : G[u]) {
    if (vis[v]) continue;
    rt = n, treeSz = sz[v];
    findRoot(v, u);
    dfs(rt);
  }
}
int main() {
  scanf("%d%d", &n, &k);
  for (int i = 1, u, v, w; i < n; i++) {
    scanf("%d%d%d", &u, &v, &w);
    G[u].push_back(make_pair(v, w));
    G[v].push_back(make_pair(u, w));
  }
  rt = n, heavySonSz[rt] = 1e9, treeSz = n;
  findRoot(0, -1);
  ans = 1e9;
  dfs(rt);
  printf("%d\n", ans > n ? -1 : ans);
}