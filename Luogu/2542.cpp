#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 5;
struct Edge {
  int u, v, c;
};
vector<Edge> edges;

// 1-index
struct LCT {
  int val[maxn], sum[maxn];  // 基于点权
  int rev[maxn], ch[maxn][2], fa[maxn];
  int stk[maxn];
  bool zero[maxn];

  inline bool isroot(int x) { return ch[fa[x]][0] != x && ch[fa[x]][1] != x; }
  inline bool get(int x) { return ch[fa[x]][1] == x; }
  inline void reverse(int x) {
    swap(ch[x][0], ch[x][1]);
    rev[x] ^= 1;
  }
  inline void set(int x) {
    sum[x] = 0;
    val[x] = 0;
    zero[x] = 1;
  }
  inline void pushdown(int x) {
    if (rev[x]) {
      if (ch[x][0]) reverse(ch[x][0]);
      if (ch[x][1]) reverse(ch[x][1]);
      rev[x] ^= 1;
    }
    if (zero[x]) {
      if (ch[x][0]) set(ch[x][0]);
      if (ch[x][1]) set(ch[x][1]);
      zero[x] = 0;
    }
  }

  // 因为儿子可能会改变，因此每次必须重新计算
  inline void pushup(int x) { sum[x] = val[x] + sum[ch[x][0]] + sum[ch[x][1]]; }

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
  // 删边
  void cut(int x, int y) { split(x, y), fa[x] = ch[y][0] = 0, pushup(y); }
  // 将x到y的路径拉到一棵Splay中，y为Splay的根
  void split(int x, int y) { makeroot(x), access(y), splay(y); }

  // 单点修改
  void update(int x, int v) {
    access(x), splay(x);
    val[x] = v;
    pushup(x);
  }

  // 区间修改
  void update_seg(int u, int v) {
    split(u, v);
    set(v);
  }
  int query(int u, int v) {
    split(u, v);
    return sum[v];
  }
} lct;

using pii = pair<int, int>;
map<pii, int> edge;

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0, u, v, c; i < m; i++) {
    scanf("%d%d", &u, &v);
    if (u > v) swap(u, v);
    edge[{u, v}]++;
  }
  for (int u, v, c;;) {
    scanf("%d", &c);
    if (c == -1) break;
    scanf("%d%d", &u, &v);
    if (u > v) swap(u, v);
    if (c == 0) edge[{u, v}]--;
    edges.push_back({u, v, c});
  }

  int tot = n + 1;
  for (auto &V : edge) {
    if (V.second == 0) continue;
    int u = V.first.first, v = V.first.second;
    while (V.second--) {
      if (lct.find(u) == lct.find(v)) {
        lct.val[tot] = 0;
        lct.update_seg(u, v);
      } else {
        lct.val[tot] = 1;
        lct.link(u, tot);
        lct.link(v, tot);
      }
      tot++;
    }
  }

  reverse(edges.begin(), edges.end());
  vector<int> ans;
  for (auto &e : edges) {
    if (e.c == 0) {
      if (lct.find(e.u) == lct.find(e.v)) {
        lct.val[tot] = 0;
        lct.update_seg(e.u, e.v);
      } else {
        lct.val[tot] = 1;
        lct.link(e.u, tot);
        lct.link(e.v, tot);
      }
      tot++;
    } else {
      ans.push_back(lct.query(e.u, e.v));
    }
  }
  reverse(ans.begin(), ans.end());
  for (auto &v : ans) printf("%d\n", v);
}