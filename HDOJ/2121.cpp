#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 1e5 + 5;
const ll INF = 1e18;
int root;
ll sum;

struct Edge {
  int u, v, id;
  ll w;
};
struct MDST {
  vector<Edge> edges;
  int vis[maxn], id[maxn];
  int pre[maxn], eid[maxn];
  ll val[maxn];
  void addEdge(int u, int v, ll w, int id) { edges.push_back({u, v, id, w}); }
  ll zhuliu(int n, int rt) {
    ll ans = 0;
    for (;;) {
      for (int i = 1; i <= n; i++) val[i] = INF, vis[i] = id[i] = 0;
      val[rt] = 0;
      for (auto &e : edges)
        if (e.u != e.v && e.w < val[e.v])
          pre[e.v] = e.u, val[e.v] = e.w, eid[e.v] = e.id;
      for (int i = 1; i <= n; i++)
        if (i != rt && val[i] == INF) return -1;
      int cnt = 0;
      for (int i = 1; i <= n; i++) {
        if (i == rt) continue;
        if (pre[i] == rt) root = eid[i];
        ans += val[i];
        if (ans >= 2 * sum) return -1;
        int u = i;
        while (vis[u] != i && !id[u] && u != rt) {
          vis[u] = i;
          u = pre[u];
        }
        if (!id[u] && u != rt) {
          id[u] = ++cnt;
          for (int v = pre[u]; v != u; v = pre[v]) id[v] = cnt;
        }
      }
      if (!cnt) break;
      for (int i = 1; i <= n; i++)
        if (!id[i]) id[i] = ++cnt;
      for (auto &e : edges) {
        if (id[e.u] != id[e.v]) e.w -= val[e.v];
        e.u = id[e.u], e.v = id[e.v];
      }
      rt = id[rt];
      n = cnt;
    }
    return ans;
  }
} mdst;
int main() {
  int n, m;
  while (~scanf("%d%d", &n, &m)) {
    mdst.edges.clear();
    ll w;
    sum = 1;
    for (int i = 0, u, v; i < m; i++) {
      scanf("%d%d%lld", &u, &v, &w);
      ++u, ++v;
      sum += w;
      mdst.addEdge(u, v, w, 0);
    }
    for (int i = 1; i <= n; i++) mdst.addEdge(n + 1, i, sum, i);
    ll ans = mdst.zhuliu(n + 1, n + 1);
    if (ans == -1)
      puts("impossible");
    else
      printf("%lld %d\n", ans - sum, root - 1);
    puts("");
  }
}