#include <bits/stdc++.h>
using namespace std;
const int maxn = 400;
int x[maxn], y[maxn];

struct MaxMatch {
  vector<int> G[maxn];
  queue<int> Q;
  int n, clk;
  int match[maxn], par[maxn];
  int Type[maxn], pre[maxn], vis[maxn];

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

int n, L;
bool ok(int i, int j) {
  int ans = abs(x[i] - x[j]) + abs(y[i] - y[j]);
  return ans <= L;
}
int main() {
  while (~scanf("%d", &n)) {
    for (int i = 1; i <= n; i++) scanf("%d%d", x + i, y + i);
    scanf("%d", &L);
    match.init(n);
    for (int i = 1; i <= n; i++) {
      for (int j = i + 1; j <= n; j++) {
        if (ok(i, j)) match.addEdge(i, j);
      }
    }
    match.work();
    bool ok = true;

    for (int i = 1; i <= n; i++) {
      if (!match.match[i]) {
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