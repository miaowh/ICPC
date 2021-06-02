#include <bits/stdc++.h>
using namespace std;
const int maxn = 805;
using pii = pair<int, int>;
vector<pii> edges;
int deg[maxn];

struct MaxMatch {
  vector<int> G[maxn];
  queue<int> Q;
  int n, clk;
  int match[maxn];
  int par[maxn];
  int Type[maxn];
  int pre[maxn];
  int vis[maxn];

  void init(int n) {
    this->n = n;
    clk = 0;
    for (int i = 1; i <= n; i++) G[i].clear(), vis[i] = 0, match[i] = 0;
  }
  void addEdge(int u, int v) {
    G[u].push_back(v);
    G[v].push_back(u);
  }

  int LCA(int x, int y) {
    clk++;
    x = par[x], y = par[y];
    while (vis[x] != clk) {
      if (x) {
        vis[x] = clk;
        x = par[pre[match[x]]];
      }
      swap(x, y);
    }
    return x;
  }
  void blossom(int x, int y, int lca) {
    while (par[x] != lca) {
      pre[x] = y;
      y = match[x];
      if (Type[y] == 1) {
        Type[y] = 0;
        Q.push(y);
      }
      par[x] = par[y] = par[lca];
      x = pre[y];
    }
  }
  int Augument(int s) {
    for (int i = 1; i <= n; i++) par[i] = i, Type[i] = -1;
    Q = queue<int>();
    Type[s] = 0;
    Q.push(s);
    while (!Q.empty()) {
      int u = Q.front();
      Q.pop();
      for (auto &v : G[u]) {
        if (Type[v] == -1) {
          pre[v] = u;
          Type[v] = 1;
          if (!match[v]) {
            for (int to = v, from = u; to; from = pre[to]) {
              match[to] = from;
              swap(match[from], to);
            }
            return true;
          }
          Type[match[v]] = 0;
          Q.push(match[v]);
        } else if (Type[v] == 0 && par[u] != par[v]) {
          int lca = LCA(u, v);
          blossom(u, v, lca);
          blossom(v, u, lca);
        }
      }
    }
    return false;
  }

  int work() {
    int ans = 0;
    for (int i = 1; i <= n; i++)
      if (!match[i]) ans += Augument(i);
    return ans;
  }
} match;

int pre[maxn];
int main() {
  int n, m, T;
  int kase = 1;
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) deg[i] = 0;
    edges.clear();
    for (int i = 0, u, v; i < m; i++) {
      scanf("%d%d", &u, &v);
      deg[u]++, deg[v]++;
      edges.push_back({u, v});
    }
    pre[0] = 1;
    for (int i = 1, x; i <= n; i++) {
      scanf("%d", &x);
      deg[i] -= x;
      pre[i] = pre[i - 1] + deg[i];
    }
    int tot = pre[n] + m * 2 - 1;

    printf("Case %d: ", kase++);
    bool ok = true;
    for (int i = 1; i <= n; i++) {
      if (deg[i] < 0) {
        puts("NO");
        ok = false;
        break;
      }
    }
    if (!ok) continue;

    match.init(tot);
    for (int i = 0; i < m; i++) {
      int u = pre[n] + i * 2, v = u + 1;
      int x = edges[i].first, y = edges[i].second;
      for (int j = pre[x - 1]; j < pre[x]; j++) match.addEdge(j, u);
      for (int j = pre[y - 1]; j < pre[y]; j++) match.addEdge(j, v);
      match.addEdge(u, v);
    }
    int ans = match.work();
    for (int i = 1; i <= tot; i++) {
      if (match.match[i] == 0) {
        ok = false;
        break;
      }
    }
    if (ok)
      puts("YES");
    else
      puts("NO");
  }
}
/*

*/