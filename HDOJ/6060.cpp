#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
const int maxn = 1e6 + 6;
vector<pii> G[maxn];
int sz[maxn];
long long ans;
int n, k;
void dfs(int u, int fa, long long val) {
  sz[u] = 1;
  for (auto &V : G[u]) {
    int v = V.first;
    int w = V.second;
    if (v == fa) continue;
    dfs(v, u, w);
    sz[u] += sz[v];
  }
  ans += val * min(sz[u], k);
}
int main() {
  while (~scanf("%d%d", &n, &k)) {
    for (int i = 1; i <= n; i++) G[i].clear();
    for (int i = 0, u, v, w; i < n - 1; i++) {
      scanf("%d%d%d", &u, &v, &w);
      G[u].push_back(make_pair(v, w));
      G[v].push_back(make_pair(u, w));
    }
    ans = 0;
    dfs(1, 0, 0);
    printf("%lld\n", ans);
  }
}