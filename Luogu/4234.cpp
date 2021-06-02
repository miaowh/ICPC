#include <bits/stdc++.h>
using namespace std;
const int maxn = 3e5 + 5;
struct Edge {
  int u, v, w;
  bool operator<(const Edge& rhs) const { return w < rhs.w; }
};
vector<Edge> edges;

struct LCT {
  int val[maxn], min[maxn], id[maxn];  // 基于点权
  int rev[maxn], ch[maxn][2], fa[maxn];
  int stk[maxn];
  inline void init(int n) {  // 初始化点权
    for (int i = 1; i <= n; i++) scanf("%d", val + i);
    for (int i = 1; i <= n; i++) fa[i] = ch[i][0] = ch[i][1] = rev[i] = 0;
  }
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
    min[x] = val[x], id[x] = x;
    if (ch[x][0] && min[ch[x][0]] < min[x])
      min[x] = min[ch[x][0]], id[x] = id[ch[x][0]];
    if (ch[x][1] && min[ch[x][1]] < min[x])
      min[x] = min[ch[x][1]], id[x] = id[ch[x][1]];
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

using pii = pair<int, int>;
map<int, pii> edge;
int a[maxn];

int main() {
  memset(lct.val, 0x3f, sizeof(lct.val));
  int n, m;
  scanf("%d%d", &n, &m);
  int tot = n + 1;
  for (int i = 0, u, v, w; i < m; i++) {
    scanf("%d%d%d", &u, &v, &w);
    if (u == v) continue;
    if (u > v) swap(u, v);
    edges.push_back({u, v, w});
  }
  sort(edges.begin(), edges.end());
  int cnt = 0;
  int ans = 0;

  int id, val;
  set<int> vis;
  for (auto& e : edges) {
    lct.val[tot] = e.w;
    a[tot] = e.w;
    edge[tot] = {e.u, e.v};

    tot++;

    if (lct.find(e.u) == lct.find(e.v)) {
      lct.split(e.u, e.v);
      val = lct.min[e.v];
      if (val >= e.w) continue;
      id = lct.id[e.v];
      lct.cut(edge[id].first, id);
      lct.cut(edge[id].second, id);
      vis.erase(id);

      id = tot - 1;
      lct.link(e.u, id);
      lct.link(e.v, id);
      vis.insert(id);
      ans = min(ans, e.w - a[*vis.begin()]);
    } else {
      id = tot - 1;
      lct.link(e.u, id);
      lct.link(e.v, id);
      vis.insert(id);
      cnt++;
      if (cnt == n - 1) ans = e.w - a[*vis.begin()];
    }
  }
  printf("%d\n", ans);
}
/*
有重边和自环！！！
*/