#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int INF = 0x3f3f3f3f;
const int maxn = 5e3 + 5;

struct Edge {
  int from, to, cap, flow, cost;
  Edge(int u, int v, int c, int f, int w)
      : from(u), to(v), cap(c), flow(f), cost(w) {}
};

struct MCMF {
  int n, m;
  vector<Edge> edges;
  vector<int> G[maxn];
  int inq[maxn];  //是否在队列中
  int d[maxn];    // bellmanford 到源点距离
  int p[maxn];    //上一条弧
  int a[maxn];    //可改进量

  void init(int n) {
    this->n = n;
    for (int i = 0; i <= n; i++) G[i].clear();
    edges.clear();
  }

  void AddEdge(int from, int to, int cap, int cost) {
    edges.push_back(Edge(from, to, cap, 0, cost));
    edges.push_back(Edge(to, from, 0, 0, -cost));
    m = edges.size();
    G[from].push_back(m - 2);
    G[to].push_back(m - 1);
  }

  bool BellmanFord(int s, int t, int& flow, ll& cost) {
    for (int i = 0; i <= n; i++) d[i] = INF;
    memset(inq, 0, sizeof(inq));
    d[s] = 0;
    inq[s] = 1;
    p[s] = 0;
    a[s] = INF;
    queue<int> Q;
    Q.push(s);
    while (!Q.empty()) {
      int u = Q.front();
      Q.pop();
      inq[u] = 0;
      for (int i = 0; i < G[u].size(); i++) {
        Edge& e = edges[G[u][i]];
        if (e.cap > e.flow && d[e.to] > d[u] + e.cost) {
          d[e.to] = d[u] + e.cost;
          p[e.to] = G[u][i];
          a[e.to] = min(a[u], e.cap - e.flow);
          if (!inq[e.to]) {
            Q.push(e.to);
            inq[e.to] = 1;
          }
        }
      }
    }
    if (d[t] == INF) return false;  // 当没有可增广的路时退出
    flow += a[t];
    cost += (ll)d[t] * (ll)a[t];
    for (int u = t; u != s; u = edges[p[u]].from) {
      edges[p[u]].flow += a[t];
      edges[p[u] ^ 1].flow -= a[t];
    }
    return true;
  }

  int MincostMaxflow(int s, int t, ll& cost) {
    int flow = 0;
    cost = 0;
    while (BellmanFord(s, t, flow, cost))
      ;
    return flow;
  }
} mcmf;
int r[maxn];

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) scanf("%d", r + i);
  int p, m, f, z, x;
  scanf("%d%d%d%d%d", &p, &m, &f, &z, &x);
  int S = 0, T = 2 * n + 1;
  mcmf.init(2 * n + 2);
  for (int i = 1; i <= n; i++) {
    mcmf.AddEdge(S, i, INF, p);
    mcmf.AddEdge(S, i + n, r[i], 0);
    mcmf.AddEdge(i, T, r[i], 0);
    if (i + m <= n) mcmf.AddEdge(i + n, i + m, INF, f);
    if (i + z <= n) mcmf.AddEdge(i + n, i + z, INF, x);
    if (i + 1 + n <= 2 * n) mcmf.AddEdge(i + n, i + 1 + n, INF, 0);
  }
  ll cost;
  mcmf.MincostMaxflow(S, T, cost);
  printf("%lld\n", cost);
}

/*
3ms/784.00KB
AC
#1
Accepted, 得分 10. ok accepted
681ms/1.60MB
AC
#2
Accepted, 得分 10. ok accepted
3ms/820.00KB
AC
#3
Accepted, 得分 10. ok accepted
3ms/760.00KB
AC
#4
Accepted, 得分 10. ok accepted
3ms/696.00KB
AC
#5
Accepted, 得分 10. ok accepted
4ms/896.00KB
AC
#6
Accepted, 得分 10. ok accepted
13ms/1.14MB
AC
#7
Accepted, 得分 10. ok accepted
106ms/1.26MB
AC
#8
Accepted, 得分 10. ok accepted
71ms/1.39MB
AC
#9
Accepted, 得分 10. ok accepted
276ms/1.50MB
AC
*/