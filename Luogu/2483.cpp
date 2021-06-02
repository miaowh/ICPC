#include <bits/stdc++.h>
using namespace std;
const int maxn = 5e3 + 5;
using ll = long long;
using pii = pair<int, double>;
using pll = pair<double, int>;
vector<pii> G[maxn];
vector<pii> rG[maxn];
int n, m;
double tot;

double d[maxn];
void dijsktra(int s, int t) {
  for (int i = 0; i <= n; i++) d[i] = 1e14;
  d[s] = 0;
  priority_queue<pll, vector<pll>, greater<pll>> pq;
  pq.push({0, s});
  while (!pq.empty()) {
    auto now = pq.top();
    pq.pop();
    int u = now.second;
    if (now.first > d[u]) continue;
    for (auto &V : rG[u]) {
      int v = V.first;
      if (d[v] > d[u] + V.second) {
        d[v] = d[u] + V.second;
        pq.push({d[v], v});
      }
    }
  }
}

struct Node {
  int u;
  double w;
  bool operator<(const Node &rhs) const { return w + d[u] > rhs.w + d[rhs.u]; }
};
int cnt[maxn];
int bfs(int s, int t) {
  for (int i = 1; i <= n; i++) cnt[i] = 0;
  int K = tot / d[s];
  priority_queue<Node> pq;
  pq.push({s, 0});
  int ans = 0;
  while (!pq.empty()) {
    auto now = pq.top();
    pq.pop();
    int u = now.u;
    if (now.w + d[u] > tot) break;
    cnt[u]++;
    if (u == t) {
      tot -= now.w;
      if (tot < 0) return ans;
      ans++;
    }
    if (cnt[u] > K) continue;
    for (auto &V : G[u]) {
      int v = V.first;
      double w = V.second;
      if (cnt[v] > K || now.w + w + d[v] > tot) continue;
      pq.push({v, now.w + w});
    }
  }
  return ans;
}

int main() {
  scanf("%d%d%lf", &n, &m, &tot);
  for (int i = 0, u, v; i < m; i++) {
    double w;
    scanf("%d%d%lf", &u, &v, &w);
    rG[v].push_back({u, w});
    G[u].push_back({v, w});
  }
  dijsktra(n, 1);
  printf("%d\n", bfs(1, n));
}