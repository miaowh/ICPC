#include <bits/stdc++.h>
using namespace std;
#define lson (rt << 1)
#define rson (rt << 1 | 1)
#define Lson l, m, lson
#define Rson m + 1, r, rson
typedef pair<int, int> pii;
const int maxn = 1e5 + 5;
vector<pii> seg[maxn << 2];

struct UFS {
  int par[maxn], h[maxn], top;
  bool dis[maxn];
  struct Node {
    int x, y, fa, h;
    bool dis;
    Node(int x = 0, int y = 0, int fa = 0, int h = 0, bool dis = 0)
        : x(x), y(y), fa(fa), h(h), dis(dis) {}
  } stk[maxn];

  void init(int n) {
    top = 0;
    for (int i = 1; i <= n; i++) par[i] = i, h[i] = 1, dis[i] = 0;
  }
  int find(int x) { return x == par[x] ? x : find(par[x]); }
  int dist(int x) { return x == par[x] ? dis[x] : dist(par[x]) ^ dis[x]; }
  void merge(int u, int v) {
    int x = find(u), y = find(v);
    if (h[x] > h[y]) swap(x, y);
    stk[top++] = Node(x, y, par[x], h[y], dis[x]);
    if (h[x] == h[y]) h[y]++;
    par[x] = y;
    dis[x] = dist(u) ^ dist(v) ^ 1;
  }
  void undo(int k) {
    for (int i = 0; i < k; i++) {
      Node it = stk[--top];
      par[it.x] = it.fa;
      h[it.y] = it.h;
      dis[it.x] = it.dis;
    }
  }
} ufs;

bool ans[maxn];

void update(int l, int r, int rt, int L, int R, int u, int v) {
  if (L <= l && R >= r) {
    seg[rt].push_back(make_pair(u, v));
    return;
  }
  int m = l + r >> 1;
  if (L <= m) update(Lson, L, R, u, v);
  if (m + 1 <= R) update(Rson, L, R, u, v);
}

void dfs(int l, int r, int rt) {
  int cnt = 0, flag = 1;
  for (int i = 0; i < seg[rt].size(); i++) {
    pii e = seg[rt][i];
    int x = ufs.find(e.first), y = ufs.find(e.second);
    if (x == y && !(ufs.dist(e.first) ^ ufs.dist(e.second))) {
      flag = 0;
      break;
    } else if (x != y) {
      cnt++;
      ufs.merge(e.first, e.second);
    }
  }
  if (flag) {
    if (l == r)
      ans[l] = true;
    else {
      int m = l + r >> 1;
      dfs(Lson);
      dfs(Rson);
    }
  }
  ufs.undo(cnt);
}

int main() {
  int n, m, T;
  scanf("%d%d%d", &n, &m, &T);
  for (int i = 0, u, v, s, t; i < m; i++) {
    scanf("%d%d%d%d", &u, &v, &s, &t);
    if (s < t) update(0, T, 1, s, t - 1, u, v);
  }
  ufs.init(n);
  dfs(0, T, 1);
  for (int i = 0; i < T; i++)
    if (ans[i])
      puts("Yes");
    else
      puts("No");
}
