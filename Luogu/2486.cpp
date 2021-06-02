#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 4;

struct LCT {
  int val[maxn], sum[maxn];  // 基于点权
  int rev[maxn], ch[maxn][2], fa[maxn];
  int stk[maxn];
  int col[maxn];
  int lc[maxn], rc[maxn];

  inline bool isroot(int x) { return ch[fa[x]][0] != x && ch[fa[x]][1] != x; }
  inline bool get(int x) { return ch[fa[x]][1] == x; }
  inline void reverse(int x) {
    swap(ch[x][0], ch[x][1]);
    swap(lc[x], rc[x]);  // !!!!!!!!!!!!!!!!!!!!!
    rev[x] ^= 1;
  }
  inline void color(int x, int v) {
    val[x] = v;
    col[x] = v;
    lc[x] = rc[x] = v;
    sum[x] = 1;
  }
  inline void pushdown(int x) {
    if (rev[x]) {
      if (ch[x][0]) reverse(ch[x][0]);
      if (ch[x][1]) reverse(ch[x][1]);
      rev[x] ^= 1;
    }
    if (col[x]) {
      if (ch[x][0]) color(ch[x][0], col[x]);
      if (ch[x][1]) color(ch[x][1], col[x]);
      col[x] = 0;
    }
  }

  // 因为儿子可能会改变，因此每次必须重新计算
  inline void pushup(int x) {
    sum[x] = 1;
    lc[x] = val[x], rc[x] = val[x];
    if (ch[x][0]) {
      sum[x] += sum[ch[x][0]];
      if (val[x] == rc[ch[x][0]]) sum[x]--;
      lc[x] = lc[ch[x][0]];
    }
    if (ch[x][1]) {
      sum[x] += sum[ch[x][1]];
      if (val[x] == lc[ch[x][1]]) sum[x]--;
      rc[x] = rc[ch[x][1]];
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
  // 区间修改
  void update_seg(int u, int v, int c) {
    split(u, v);
    color(v, c);
  }
  int query(int u, int v) {
    split(u, v);
    return sum[v];
  }
} lct;

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 1, c; i <= n; i++) {
    scanf("%d", &c);
    lct.val[i] = c;
    lct.lc[i] = c;
    lct.rc[i] = c;
  }
  for (int i = 0, u, v; i < n - 1; i++) {
    scanf("%d%d", &u, &v);
    lct.link(u, v);
  }
  int a, b, c;
  char op[5];
  while (m--) {
    scanf("%s%d%d", op, &a, &b);
    if (op[0] == 'C') {
      scanf("%d", &c);
      lct.update_seg(a, b, c);
    } else {
      printf("%d\n", lct.query(a, b));
    }
  }
}