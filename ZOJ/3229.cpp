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
int G[maxn], in[maxn];

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
  void AddEdge(int from, int to, int cap) {
    edges.emplace_back(from, to, cap, 0);
    edges.emplace_back(to, from, 0, 0);
    m = edges.size();
    G[from].push_back(m - 2);
    G[to].push_back(m - 1);
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
        Edge& e = edges[G[x][i]];
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
      Edge& e = edges[G[x][i]];
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
} dinic;

int n, m;
int C[400];
int ans[400][1005], id[400][1005];
void getans() {
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < C[i]; j++) {
      ans[i][j] += dinic.edges[id[i][j]].flow;
      printf("%d\n", ans[i][j]);
    }
  }
}
int main() {
  while (~scanf("%d%d", &n, &m)) {
    int s = n + m + 1, t = n + m + 2, ss = n + m + 3, tt = n + m + 4;
    dinic.init(tt);
    for (int i = 0; i <= tt; i++) in[i] = 0;
    for (int i = 1, g; i <= m; i++) {
      scanf("%d", &g);
      in[n + i] -= g;
      in[t] += g;
      dinic.AddEdge(n + i, t, INF);
    }
    for (int i = 1, D; i <= n; i++) {
      scanf("%d%d", C + i, &D);
      dinic.AddEdge(s, i, D);
      for (int j = 0, x, l, r; j < C[i]; j++) {
        scanf("%d%d%d", &x, &l, &r);
        x++;
        dinic.AddEdge(i, x + n, r - l);
        in[i] -= l;
        in[x + n] += l;

        id[i][j] = dinic.edges.size() - 2;
        ans[i][j] = l;
      }
    }
    int sum = 0;
    for (int i = 1; i < ss; i++) {
      if (in[i] > 0)
        dinic.AddEdge(ss, i, in[i]), sum += in[i];
      else if (in[i] < 0)
        dinic.AddEdge(i, tt, -in[i]);
    }
    dinic.AddEdge(t, s, INF);

    int flow = dinic.Maxflow(ss, tt);
    if (flow != sum) {
      puts("-1\n");
      continue;
    }
    flow = dinic.Maxflow(s, t);
    printf("%d\n", flow);
    getans();
    puts("");
  }
}