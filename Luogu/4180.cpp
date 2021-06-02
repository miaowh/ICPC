#include <bits/stdc++.h>
using namespace std;
const int maxn = 4e5 + 5;
using ll = long long;
struct Edge {
  int u, v, w;
  bool operator<(const Edge &rhs) const { return w < rhs.w; }
};
vector<Edge> edges;
int n, m;

struct LCT {
  int val[maxn], max[maxn], smax[maxn];  // 基于点权
  int rev[maxn], ch[maxn][2], fa[maxn];
  int stk[maxn];
  inline bool isroot(int x) { return ch[fa[x]][0] != x && ch[fa[x]][1] != x; }
  inline bool get(int x) { return ch[fa[x]][1] == x; }
  inline void reverse(int x) {
    swap(ch[x][0], ch[x][1]);
    rev[x] ^= 1;
  }
  inline void pushdown(int x) {
    if (rev[x]) {
      if (ch[x][0]) reverse(ch[x][0]);
      if (ch[x][1]) reverse(ch[x][1]);
      rev[x] ^= 1;
    }
  }

  // 因为儿子可能会改变，因此每次必须重新计算
  int tmp[10];
  inline void pushup(int x) {
    int tot = 0;
    tmp[tot++] = val[x];
    max[x] = val[x];
    if (ch[x][0]) {
      tmp[tot++] = max[ch[x][0]];
      tmp[tot++] = smax[ch[x][0]];
      max[x] = std::max(max[x], max[ch[x][0]]);
    }
    if (ch[x][1]) {
      tmp[tot++] = max[ch[x][1]];
      tmp[tot++] = smax[ch[x][1]];
      max[x] = std::max(max[x], max[ch[x][1]]);
    }
    smax[x] = -1;
    for (int i = 0; i < tot; i++)
      if (tmp[i] < max[x] && tmp[i] > smax[x]) smax[x] = tmp[i];
  }
  // 避免单独使用：不能直接旋转根
  void rotate(int x) {
    int y = fa[x], z = fa[y], d = get(x);
    if (!isroot(y)) ch[z][get(y)] = x;
    fa[x] = z;
    ch[y][d] = ch[x][d ^ 1], fa[ch[y][d]] = y;
    ch[x][d ^ 1] = y, fa[y] = x;
    pushup(y), pushup(x);
  }
  // 将x旋转到Splay的根
  void splay(int x) {
    int top = 0;
    stk[++top] = x;
    for (int i = x; !isroot(i); i = fa[i]) stk[++top] = fa[i];
    for (int i = top; i; i--) pushdown(stk[i]);
    for (int f; !isroot(x); rotate(x))
      if (!isroot(f = fa[x])) rotate(get(x) == get(f) ? f : x);
  }

  // 将根到x的路径拉到一棵Splay中
  void access(int x) {
    for (int y = 0; x; y = x, x = fa[x]) splay(x), ch[x][1] = y, pushup(x);
  }
  // 让x成为原树的根，x为深度最低的点，其左子树为空
  void makeroot(int x) { access(x), splay(x), reverse(x); }

  // 找x所在原树的根。主要用来判联通性，如果find(x) = find(y)
  // 则x,y在同一棵树中。
  int find(int x) {
    access(x), splay(x);
    while (ch[x][0]) pushdown(x), x = ch[x][0];
    splay(x);
    return x;
  }
  // 加边，y为深度最低的点（顺序无所谓）
  void link(int x, int y) {
    makeroot(x);
    fa[x] = y, splay(x);
  }

  // 将x到y的路径拉到一棵Splay中，y为Splay的根
  void split(int x, int y) { makeroot(x), access(y), splay(y); }
} lct;

bool vis[maxn];
int par[maxn];
int find(int x) { return x == par[x] ? x : par[x] = find(par[x]); }
inline void merge(int x, int y) {
  x = find(x);
  y = find(y);
  par[x] = y;
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) par[i] = i;

  for (int i = 0, u, v, w; i < m; i++) {
    scanf("%d%d%d", &u, &v, &w);
    edges.push_back({u, v, w});
  }
  sort(edges.begin(), edges.end());
  int cnt = 0;
  ll tot = 0;
  for (int i = 0, u, v, w; i < m; i++) {
    u = edges[i].u;
    v = edges[i].v;
    w = edges[i].w;
    if (find(u) == find(v)) continue;
    merge(u, v);
    lct.link(u, i + 1 + n);
    lct.link(v, i + 1 + n);
    lct.val[i + 1 + n] = w;

    cnt++;
    tot += w;
    vis[i] = true;
    if (cnt == n - 1) break;
  }
  ll ans = 1e18;
  for (int i = 0, u, v, w; i < m; i++) {
    u = edges[i].u;
    v = edges[i].v;
    w = edges[i].w;
    if (vis[i]) continue;
    lct.split(u, v);

    ll tmp = tot - lct.max[v] + w;
    if (tmp != tot) ans = min(ans, tmp);
    tmp = tot - lct.smax[v] + w;
    if (tmp != tot) ans = min(ans, tmp);
  }
  printf("%lld\n", ans);
}