#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e4 + 5;
int a[maxn];

struct LCT {
  int sum[maxn];  // 基于点权
  int rev[maxn], ch[maxn][2], fa[maxn];
  int stk[maxn];
  inline void init(int n) {  // 初始化点权
    for (int i = 1; i <= n; i++)
      fa[i] = ch[i][0] = ch[i][1] = rev[i] = sum[i] = 0;
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
    sum[x] = max({a[x], sum[ch[x][0]], sum[ch[x][1]]});
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
  // 加边（x 连到 y），y为深度最低的点
  void link(int x, int y) {
    makeroot(x);
    // if(find(y) != x) fa[x] = y; // 存在不合法加边
    fa[x] = y, splay(x);
  }
  // 删边
  void cut(int x, int y) {
    split(x, y), fa[x] = ch[y][0] = 0, pushup(y);
    /*
      存在不合法删边
      makeroot(x);
      if(find(y) != x || fa[y] != x || ch[y][0]) return false;
      fa[y] = ch[x][1] = 0;
      pushup(x);
      return true;
    */
  }
  // 将x到y的路径拉到一棵Splay中，y为Splay的根
  void split(int x, int y) { makeroot(x), access(y), splay(y); }

  void update(int x, int v) { a[x] = v, access(x), splay(x); }
} lct[10];

map<int, int> color[maxn];
int d[maxn][10];

int main() {
  // freopen("network.in", "r", stdin);
  // freopen("network.out", "w", stdout);

  int n, m, c, k;
  scanf("%d%d%d%d", &n, &m, &c, &k);
  for (int i = 1; i <= n; i++) scanf("%d", a + i);
  for (int i = 0; i < c; i++) lct[i].init(n);
  for (int i = 0, u, v, w; i < m; i++) {
    scanf("%d%d%d", &u, &v, &w);
    if (u > v) swap(u, v);
    color[u][v] = w;
    d[u][w]++, d[v][w]++;
    lct[w].link(u, v);
  }
  int op, x, y, u, v, w;
  while (k--) {
    scanf("%d", &op);
    if (op == 0) {
      scanf("%d%d", &x, &y);
      for (int i = 0; i < c; i++) lct[i].update(x, y);
    } else if (op == 1) {
      scanf("%d%d%d", &u, &v, &w);
      if (u > v) swap(u, v);
      if (color[u].find(v) == color[u].end()) {
        puts("No such edge.");
        continue;
      }
      int tmp = color[u][v];
      if (tmp == w) {
        puts("Success.");
        continue;  // !!
      }
      if (d[u][w] == 2 || d[v][w] == 2) {
        puts("Error 1.");
        continue;
      }
      if (lct[w].find(u) == lct[w].find(v)) {
        puts("Error 2.");
        continue;
      }
      puts("Success.");

      lct[tmp].cut(u, v);
      d[u][tmp]--, d[v][tmp]--;

      lct[w].link(u, v);
      d[u][w]++, d[v][w]++;
      color[u][v] = w;
    } else {
      scanf("%d%d%d", &w, &u, &v);
      if (lct[w].find(u) != lct[w].find(v))
        puts("-1");
      else {
        lct[w].split(u, v);
        printf("%d\n", lct[w].sum[v]);
      }
    }
  }
}