#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e4 + 6;
const int INF = 0x3f3f3f3f;
struct Edge {
  int u, v;
  int cap, flow;
  Edge(int u_, int v_, int cap_, int flow_)
      : u(u_), v(v_), cap(cap_), flow(flow_) {}
};

struct Dinic {
  int n, m, s, t;  //结点数，边数（包括反向弧），源点编号和汇点编号
  vector<Edge> edges;  //边表。edge[e]和edge[e^1]互为反向弧
  vector<int> G[maxn];  //邻接表，G[i][j]表示节点i的第j条边在e数组中的序号
  bool vis[maxn];  // BFS使用
  int d[maxn];     //从起点到i的距离
  int cur[maxn];   //当前弧下标
  void init(int n) {
    this->n = n;
    for (int i = 0; i <= n; i++) G[i].clear();
    edges.clear();
  }
  int AddEdge(int from, int to, int cap) {
    edges.emplace_back(from, to, cap, 0);
    edges.emplace_back(to, from, 0, 0);
    m = edges.size();
    G[from].push_back(m - 2);
    G[to].push_back(m - 1);
    return m - 2;
  }
  bool BFS() {
    for (int i = 0; i <= n; ++i) vis[i] = false, d[i] = 0;
    queue<int> q;
    q.push(s);
    d[s] = 0;
    vis[s] = 1;
    while (!q.empty()) {
      int x = q.front();
      q.pop();
      for (int i = 0, v; i < G[x].size(); i++) {
        Edge &e = edges[G[x][i]];
        v = e.v;
        if (!vis[v] && e.cap > e.flow) {
          vis[v] = 1;
          d[v] = d[x] + 1;
          q.push(v);
        }
      }
    }
    return vis[t];
  }
  int DFS(int x, int a) {
    if (x == t || a == 0) return a;
    int flow = 0, f;
    for (int &i = cur[x], v; i < G[x].size(); i++) {  //从上次考虑的弧
      Edge &e = edges[G[x][i]];
      v = e.v;
      if (d[x] + 1 == d[v] && (f = DFS(v, min(a, e.cap - e.flow))) > 0) {
        e.flow += f;
        edges[G[x][i] ^ 1].flow -= f;
        flow += f;
        a -= f;
        if (a == 0) break;
      }
    }
    return flow;
  }
  int Maxflow(int s, int t) {
    this->s = s, this->t = t;
    int flow = 0;
    while (BFS()) {
      for (int i = 0; i <= n; i++) cur[i] = 0;
      flow += DFS(s, INF);
    }
    return flow;
  }

  int edge_id[maxn];  // 每条边的编号
  vector<int> cut;    // 割边的编号
  bool ok[maxn];
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
      if (e.cap == e.flow) {
        if (e.u == s || e.v == s) {
          ok[e.u] = ok[e.v] = 0;
        } else {
          ok[e.u] = ok[e.v] = 1;
        }
      }
    }
  }
} dinic;

int main() {
  int m, n;
  scanf("%d%d", &m, &n);
  int s = n + m, t = s + 1;
  dinic.init(t);
  int sum = 0;
  int sz = 0;
  for (int i = 0, w; i < m; i++) {
    scanf("%d", &w);
    sum += w;
    dinic.edge_id[sz++] = dinic.AddEdge(s, i, w);
    char ch;
    while (true) {
      scanf("%d%c", &w, &ch);
      dinic.AddEdge(i, w + m - 1, INF);
      if (ch == '\r' || ch == '\n') break;
    }
  }
  for (int i = 0, w; i < n; i++) {
    scanf("%d", &w);
    dinic.edge_id[sz++] = dinic.AddEdge(m + i, t, w);
  }
  int flow = dinic.Maxflow(s, t);

  for (int i = 0; i < m; i++) dinic.ok[i] = 1;
  for (int i = 0; i < n; i++) dinic.ok[i + m] = 0;
  dinic.findCut(sz);
  for (int i = 0; i < m; i++)
    if (dinic.ok[i]) printf("%d ", i + 1);
  puts("");
  for (int i = 0; i < n; i++)
    if (dinic.ok[i + m]) printf("%d ", i + 1);
  puts("");

  printf("%d\n", sum - flow);
}