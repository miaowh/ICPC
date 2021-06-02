#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 5;
struct Edge {
  int u, v, w;
  bool operator<(const Edge &e) const { return w < e.w; }
};
vector<Edge> edges;
unordered_map<int, int> edge[maxn];
unordered_map<int, pair<int, int>> rmap;
bool vis[maxn];
int a[maxn];

struct LCT {
  int val[maxn], sum[maxn], id[maxn];  // 基于点权
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
    // if(val[x] < sum[x]) sum[x] = val[x]; !!
    // 不能和自己比较，因为儿子可能已经变了，以前的信息是假的。
    sum[x] = val[x], id[x] = x;
    if (sum[ch[x][0]] > sum[x]) sum[x] = sum[ch[x][0]], id[x] = id[ch[x][0]];
    if (sum[ch[x][1]] > sum[x]) sum[x] = sum[ch[x][1]], id[x] = id[ch[x][1]];
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
  // 让x成为原树的根
  void makeroot(int x) { access(x), splay(x), reverse(x); }

  // 找x所在原树的根。主要用来判联通性，如果find(x) = find(y)
  // 则x,y在同一棵树中。
  int find(int x) {
    access(x), splay(x);
    while (ch[x][0]) pushdown(x), x = ch[x][0];
    splay(x);
    return x;
  }
  // 加边（x 连到 y）
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

using t3 = tuple<int, int, int>;
int main() {
  int n, m, q;
  scanf("%d%d%d", &n, &m, &q);
  int tot = n + 1;
  for (int i = 0, u, v, w; i < m; i++) {
    scanf("%d%d%d", &u, &v, &w);
    if (u > v) swap(u, v);
    lct.val[tot] = w;
    a[tot] = w;
    edge[u][v] = tot;
    rmap[tot] = {u, v};
    tot++;
  }

  vector<t3> query;
  int op, x, y, id;
  for (int i = 0; i < q; i++) {
    scanf("%d%d%d", &op, &x, &y);
    if (x > y) swap(x, y);
    query.push_back({op, x, y});
    if (op == 2) vis[edge[x][y]] = 1;
  }
  for (int i = n + 1; i < tot; i++) {
    if (vis[i]) continue;
    edges.push_back({rmap[i].first, rmap[i].second, a[i]});
  }
  sort(edges.begin(), edges.end());
  for (auto &e : edges) {
    if (lct.find(e.u) == lct.find(e.v)) continue;
    id = edge[e.u][e.v];
    lct.link(e.u, id);
    lct.link(e.v, id);
  }
  vector<int> ans;
  for (int i = q - 1; i >= 0; i--) {
    op = get<0>(query[i]);
    x = get<1>(query[i]);
    y = get<2>(query[i]);
    if (op == 1) {
      lct.split(x, y);
      ans.push_back(lct.sum[y]);
    } else {
      lct.split(x, y);
      int tmp = lct.id[y];
      id = edge[x][y];
      if (a[tmp] <= a[id]) continue;
      lct.cut(rmap[tmp].first, tmp);
      lct.cut(rmap[tmp].second, tmp);
      lct.link(x, id);
      lct.link(y, id);
    }
  }
  for (int i = ans.size() - 1; i >= 0; i--) printf("%d\n", ans[i]);
}