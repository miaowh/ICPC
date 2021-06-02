#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5;
const int INF = 0x3f3f3f3f;
int edge_id[maxn];

struct Edge {
  int u, v, cap, flow;
  Edge(int u = 0, int v = 0, int c = 0, int f = 0)
      : u(u), v(v), cap(c), flow(f) {}
};
struct Dinic {
  int n, s, t;
  vector<Edge> edges;
  vector<int> G[maxn];
  int d[maxn], cur[maxn];
  void init(int n) {
    this->n = n;
    for (int i = 0; i <= n; i++) G[i].clear();
    edges.clear();
  }
  int addEdge(int u, int v, int c) {
    edges.push_back({u, v, c, 0});
    edges.push_back({v, u, 0, 0});
    int m = edges.size();
    G[u].push_back(m - 2);
    G[v].push_back(m - 1);
    return m - 2;
  }

  bool BFS() {
    for (int i = 0; i <= n; i++) d[i] = 0;
    d[s] = 1;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      int v;
      for (auto &id : G[u]) {
        auto &e = edges[id];
        v = e.v;
        if (!d[v] && e.cap > e.flow) {
          d[v] = d[u] + 1;
          q.push(v);
        }
      }
    }
    if (d[t]) return true;
    return false;
  }
  int DFS(int u, int f) {
    if (u == t || f == 0) return f;
    int v, a, flow = 0;
    for (int &i = cur[u]; i < G[u].size(); i++) {
      auto &e = edges[G[u][i]];
      v = e.v;
      if (d[v] == d[u] + 1 && (a = DFS(v, min(f, e.cap - e.flow))) > 0) {
        e.flow += a;
        edges[G[u][i] ^ 1].flow -= a;
        flow += a;
        f -= a;
        if (f == 0) break;
      }
    }
    return flow;
  }
  int MaxFlow(int s, int t) {
    this->s = s, this->t = t;
    int flow = 0;
    while (BFS()) {
      for (int i = 0; i <= n; i++) cur[i] = 0;
      flow += DFS(s, INF);
    }
    return flow;
  }

  bool vis[maxn];

  int edge_id[maxn];  // 每条边的编号
  vector<int> cut;    // 割边的编号
  void findCut(int m) {
    cut.clear();
    for (int i = 0; i <= n; i++) vis[i] = 0;
    queue<int> q;
    q.push(s);
    vis[s] = 1;
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (auto &id : G[u]) {
        auto &e = edges[id];
        if (!vis[e.v] && e.cap > e.flow) {
          vis[e.v] = 1;
          q.push(e.v);
        }
      }
    }
    for (int i = 0; i < m; i++) {
      auto &e = edges[edge_id[i]];
      if (vis[e.u] == vis[e.v]) continue;
      if (e.cap == e.flow) cut.push_back(i + 1);  // 1-index
    }
  }
} dinic;

int main() {
  int T, kase = 1;
  scanf("%d", &T);
  while (T--) {
    int n, m, f;
    scanf("%d%d%d", &n, &m, &f);
    int s = 0, t = 1;
    dinic.init(n);
    for (int i = 0, u, v, w; i < m; i++) {
      scanf("%d%d%d", &u, &v, &w);
      edge_id[i] = dinic.addEdge(v, u, w);
    }
    int sum = 0;
    for (int i = 0, u, w; i < f; i++) {
      scanf("%d%d", &u, &w);
      sum += w;
      dinic.addEdge(s, u, w);
    }
    int flow = dinic.MaxFlow(s, t);
    printf("Case %d: %d\n", kase++, sum - flow);

    dinic.findCut(m);
    printf("%d", dinic.cut.size());
    for (int i = 0; i < dinic.cut.size(); i++) {
      printf(" %d", dinic.cut[i]);
    }
    puts("");
  }
}