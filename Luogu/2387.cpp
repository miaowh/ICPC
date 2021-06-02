#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 5;
struct Edge {
  int u, v, a, b;
  bool operator<(const Edge &rhs) const { return a < rhs.a; }
};
vector<Edge> edges;
int n, m;

struct LCT {
  int val[maxn], id[maxn];  // 基于点权
  int rev[maxn], ch[maxn][2], fa[maxn];
  int stk[maxn];
  inline bool isroot(int x) { return ch[fa[x]][0] != x && ch[fa[x]][1] != x; }
  inline bool get(int x) { return ch[fa[x]][1] == x; }
  inline void reverse(int x) {
    swap(ch[x][0], ch[x][1]);
    rev[x] ^= 1;
  }
  inline void pushdown(int x) {
    if (!rev[x]) return;
    if (ch[x][0]) reverse(ch[x][0]);
    if (ch[x][1]) reverse(ch[x][1]);
    rev[x] ^= 1;
  }
  inline void pushup(int x) {
    id[x] = x;
    if (val[id[ch[x][0]]] > val[id[x]]) id[x] = id[ch[x][0]];
    if (val[id[ch[x][1]]] > val[id[x]]) id[x] = id[ch[x][1]];
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
    // 父亲不认儿子，但儿子认父亲
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

  void update(int x, int v) { val[x] = v, access(x), splay(x); }
} lct;

map<int, Edge> edge;
int main() {
  scanf("%d%d", &n, &m);
  for (int i = 0, u, v, a, b; i < m; i++) {
    scanf("%d%d%d%d", &u, &v, &a, &b);
    if (u == v) continue;
    edges.push_back({u, v, a, b});
  }
  int ans = 1e9;
  int tot = n + 1, cnt = 0;
  sort(edges.begin(), edges.end());
  for (auto &e : edges) {
    edge[tot] = e;
    lct.val[tot] = e.b;

    if (lct.find(e.u) == lct.find(e.v)) {
      lct.split(e.u, e.v);
      int id = lct.id[e.v];
      if (lct.val[id] <= e.b) continue;
      lct.cut(edge[id].u, id);
      lct.cut(edge[id].v, id);

      lct.link(e.u, tot);
      lct.link(e.v, tot);
      if (lct.find(1) == lct.find(n)) {
        lct.split(1, n);
        ans = min(ans, lct.val[lct.id[n]] + e.a);
      }
    } else {
      lct.link(e.u, tot);
      lct.link(e.v, tot);
      if (lct.find(1) == lct.find(n)) {
        lct.split(1, n);
        ans = min(ans, lct.val[lct.id[n]] + e.a);
      }
    }
    tot++;
  }
  printf("%d\n", ans == 1e9 ? -1 : ans);
}