#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 5;
const int mod = 51061;

struct LCT {
  int val[maxn], sum[maxn];  // 基于点权
  int sz[maxn];
  int lazyAdd[maxn], lazyMul[maxn];
  int rev[maxn], ch[maxn][2], fa[maxn];
  int stk[maxn];
  inline void init(int n) {  // 初始化点权
    for (int i = 1; i <= n; i++) val[i] = 1;
    for (int i = 1; i <= n; i++)
      fa[i] = ch[i][0] = ch[i][1] = rev[i] = 0, lazyMul[i] = 1;
  }
  inline bool isroot(int x) { return ch[fa[x]][0] != x && ch[fa[x]][1] != x; }
  inline bool get(int x) { return ch[fa[x]][1] == x; }
  inline void reverse(int x) {
    swap(ch[x][0], ch[x][1]);
    rev[x] ^= 1;
  }
  inline void pushadd(int x, int w) {
    sum[x] = (sum[x] + 1LL * w * sz[x] % mod) % mod;
    val[x] = (val[x] + w) % mod;
    lazyAdd[x] = (lazyAdd[x] + w) % mod;
  }
  inline void pushmul(int x, int w) {
    sum[x] = 1LL * sum[x] * w % mod;
    val[x] = 1LL * val[x] * w % mod;
    lazyMul[x] = 1LL * lazyMul[x] * w % mod;
    lazyAdd[x] = 1LL * lazyAdd[x] * w % mod;
  }
  inline void pushdown(int x) {
    if (lazyMul[x] != 1) {
      if (ch[x][0]) pushmul(ch[x][0], lazyMul[x]);
      if (ch[x][1]) pushmul(ch[x][1], lazyMul[x]);
      lazyMul[x] = 1;
    }
    if (lazyAdd[x]) {
      if (ch[x][0]) pushadd(ch[x][0], lazyAdd[x]);
      if (ch[x][1]) pushadd(ch[x][1], lazyAdd[x]);
      lazyAdd[x] = 0;
    }

    if (rev[x]) {
      if (ch[x][0]) reverse(ch[x][0]);
      if (ch[x][1]) reverse(ch[x][1]);
      rev[x] ^= 1;
    }
  }
  inline void pushup(int x) {
    sum[x] = (val[x] + sum[ch[x][0]] + sum[ch[x][1]]) % mod;
    sz[x] = 1 + sz[ch[x][0]] + sz[ch[x][1]];
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
    // if (find(y) != x) fa[x] = y;  // 存在不合法加边
    fa[x] = y, splay(x);
  }
  // 删边
  void cut(int x, int y) {
    split(x, y), fa[x] = ch[y][0] = 0, pushup(y);
    // /*
    // 存在不合法删边
    // makeroot(x);
    // if (find(y) != x || fa[y] != x || ch[y][0]) return;
    // fa[y] = ch[x][1] = 0;
    // pushup(x);
    // */
  }
  // 将x到y的路径拉到一棵Splay中，y为Splay的根
  void split(int x, int y) {
    makeroot(x);
    access(y);
    splay(y);
  }

  void add(int x, int v) {
    pushadd(x, v);
    access(x), splay(x);
  }
  void mul(int x, int v) {
    pushmul(x, v);
    access(x), splay(x);
  }
} lct;

int main() {
  int n, q;
  scanf("%d%d", &n, &q);
  lct.init(n);
  for (int i = 0, u, v; i < n - 1; i++) {
    scanf("%d%d", &u, &v);
    lct.link(u, v);
  }
  char op[10];
  int u, v, c, x, y;
  while (q--) {
    scanf("%s", op);
    switch (op[0]) {
      case '+':
        scanf("%d%d%d", &u, &v, &c);
        lct.split(u, v);
        lct.add(v, c);
        break;
      case '-':
        scanf("%d%d%d%d", &u, &v, &x, &y);
        lct.cut(u, v);
        lct.link(x, y);
        break;
      case '*':
        scanf("%d%d%d", &u, &v, &c);
        lct.split(u, v);
        lct.mul(v, c);
        break;
      case '/':
        scanf("%d%d", &u, &v);
        lct.split(u, v);
        printf("%d\n", lct.sum[v]);
        break;
    }
  }
}