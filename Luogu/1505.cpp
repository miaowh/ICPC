#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 5;
int n;

struct LCT {
  int val[maxn], sum[maxn];  // 基于点权
  int max[maxn], min[maxn];
  int oppo[maxn];
  int rev[maxn], ch[maxn][2], fa[maxn];
  int stk[maxn];
  inline bool isroot(int x) { return ch[fa[x]][0] != x && ch[fa[x]][1] != x; }
  inline bool get(int x) { return ch[fa[x]][1] == x; }
  inline void reverse(int x) {
    swap(ch[x][0], ch[x][1]);
    rev[x] ^= 1;
  }
  inline void opposite(int x) {
    sum[x] *= -1;
    max[x] *= -1;
    min[x] *= -1;
    val[x] *= -1;
    swap(min[x], max[x]);
    oppo[x] ^= 1;
  }
  inline void pushdown(int x) {
    if (rev[x]) {
      if (ch[x][0]) reverse(ch[x][0]);
      if (ch[x][1]) reverse(ch[x][1]);
      rev[x] ^= 1;
    }
    if (oppo[x]) {
      if (ch[x][0]) opposite(ch[x][0]);
      if (ch[x][1]) opposite(ch[x][1]);
      oppo[x] ^= 1;
    }
  }
  inline void pushup(int x) {
    sum[x] = val[x] + sum[ch[x][0]] + sum[ch[x][1]];
    min[x] = std::min(min[ch[x][0]], min[ch[x][1]]);
    max[x] = std::max(max[ch[x][0]], max[ch[x][1]]);
    if (x > n) {
      min[x] = std::min(val[x], min[x]);
      max[x] = std::max(val[x], max[x]);
    }
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

  void update(int x, int v) {
    access(x), splay(x);
    val[x] = v;
    pushup(x);
  }
  void update_oppo(int x, int y) {
    split(x, y);
    opposite(y);
  }
} lct;

int main() {
  scanf("%d", &n);
  lct.min[0] = 1e9, lct.max[0] = -1e9;
  for (int i = 1, u, v, w; i <= n - 1; i++) {
    scanf("%d%d%d", &u, &v, &w);
    ++u, ++v;
    lct.val[i + n] = w;
    lct.link(u, i + n);
    lct.link(v, i + n);
  }
  int m;
  scanf("%d", &m);
  char op[10];
  int u, v;
  while (m--) {
    scanf("%s", op);
    scanf("%d%d", &u, &v);
    switch (op[0]) {
      case 'S':
        ++u, ++v;
        lct.split(u, v);
        printf("%d\n", lct.sum[v]);
        break;
      case 'N':
        ++u, ++v;
        lct.update_oppo(u, v);
        break;
      case 'C':
        lct.update(u + n, v);
        break;
      case 'M':
        ++u, ++v;
        lct.split(u, v);
        printf("%d\n", op[1] == 'A' ? lct.max[v] : lct.min[v]);
        break;
    }
  }
}