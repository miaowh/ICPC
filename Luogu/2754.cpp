#include <bits/stdc++.h>
using namespace std;
const int maxn = 100;
int r[maxn], p[maxn], s[maxn][maxn];
const int INF = 0x3f3f3f3f;
struct Edge {
  int u, v, cap, flow;
  Edge(int u, int v, int c, int f) : u(u), v(v), cap(c), flow(f) {}
};

struct Dinic {
  vector<Edge> edges;
  vector<int> G[maxn];
  int n, s, t, d[maxn], cur[maxn];
  bool vis[maxn];

  void init(int n) {
    this->n = n;
    edges.clear();
    for (int i = 0; i <= n; i++) G[i].clear();
  }
  void addedge(int u, int v, int cap) {
    edges.push_back({u, v, cap, 0});
    edges.push_back({v, u, 0, 0});
    int m = edges.size();
    G[u].push_back(m - 2);
    G[v].push_back(m - 1);
  }
  bool bfs() {
    for (int i = 0; i <= n; i++) vis[i] = 0, d[i] = 0;
    queue<int> q;
    q.push(s);
    vis[s] = 1;
    while (!q.empty()) {
      int x = q.front();
      q.pop();
      for (auto &id : G[x]) {
        auto &e = edges[id];
        if (!vis[e.v] && e.cap > e.flow) {
          vis[e.v] = 1;
          d[e.v] = d[x] + 1;
          q.push(e.v);
        }
      }
    }
    return vis[t];
  }
  int dfs(int x, int a) {
    if (x == t || a == 0) return a;
    int flow = 0, f;
    for (int &i = cur[x], v; i < G[x].size(); i++) {
      auto &e = edges[G[x][i]];
      v = e.v;
      if (d[x] + 1 == d[v] && (f = dfs(v, min(a, e.cap - e.flow))) > 0) {
        e.flow += f;
        edges[G[x][i] ^ 1].flow -= f;
        flow += f;
        a -= f;
        if (a == 0) break;
      }
    }
    return flow;
  }
  int maxFlow(int s, int t) {
    this->s = s, this->t = t;
    int flow = 0;
    while (bfs()) {
      for (int i = 0; i <= n; i++) cur[i] = 0;
      flow += dfs(s, INF);
    }
    return flow;
  }
} dinic;

int main() {
  int n, m, k;
  scanf("%d%d%d", &n, &m, &k);
  for (int i = 0; i < m; i++) {
    scanf("%d%d", p + i, r + i);
    for (int j = 0; j < r[i]; j++) scanf("%d", &s[i][j]);
  }
  dinic.init(n);
}