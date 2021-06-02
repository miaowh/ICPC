// 没过
#include <bits/stdc++.h>
using namespace std;
const int maxn = 6e5 + 5;
const int N = 4e6 + 6;
const int INF = 1e9;
struct Node {
  int val, sum, lazy;
  int lmx, mx, rmx;
  bool rev;
  Node(int val = 0) {
    this->val = val;
    mx = sum = val;
    lmx = rmx = max(0, val);
    lazy = INF;
    rev = 0;
  }
};
int a[maxn];

#define key_value ch[ch[rt][1]][0]
struct Splay {
  int sz[maxn], ch[maxn][2], fa[maxn];
  Node key[maxn];
  int rt, tot;
  int stk[maxn], top;

  // 1-index
  void init(int n) {
    tot = top = 0;
    rt = newnode(0, Node(-INF));
    ch[rt][1] = newnode(rt, Node(-INF));
    key_value = build(1, n, ch[rt][1]);
    pushup(ch[rt][1]), pushup(rt);
  }

  int build(int l, int r, int p) {
    if (l > r) return 0;
    int m = l + r >> 1;
    int x = newnode(p, Node(a[m]));  // a[i]
    ch[x][0] = build(l, m - 1, x);
    ch[x][1] = build(m + 1, r, x);
    pushup(x);
    return x;
  }

  int newnode(int p, Node k) {
    int x = top ? stk[top--] : ++tot;
    fa[x] = p, sz[x] = 1, key[x] = k;
    ch[x][0] = ch[x][1] = 0;
    return x;
  }

  void pushup(int x) {
    if (!x) return;
    sz[x] = 1 + sz[ch[x][0]] + sz[ch[x][1]];
    Node &o = key[x], &ls = key[ch[x][0]], &rs = key[ch[x][1]];
    o.sum = ls.sum + rs.sum + o.val;
    o.lmx = max(ls.lmx, ls.sum + rs.lmx + o.val);
    o.rmx = max(rs.rmx, rs.sum + ls.rmx + o.val);
    o.mx = max(max(ls.mx, rs.mx), ls.rmx + o.val + rs.lmx);
  }

  void f1(int u) {
    swap(ch[u][0], ch[u][1]);
    swap(key[u].lmx, key[u].rmx);  // !!!
    key[u].rev ^= 1;
  }
  void f2(int u, int c) {
    Node &o = key[u];
    o.val = c;
    o.sum = sz[u] * c;
    o.lmx = o.rmx = max(0, o.sum);
    o.mx = max(o.sum, o.val);
    o.lazy = c;
  }
  void pushdown(int x) {
    if (key[x].rev) {
      if (ch[x][0]) f1(ch[x][0]);
      if (ch[x][1]) f1(ch[x][1]);
      key[x].rev = 0;
    }
    if (key[x].lazy != INF) {
      if (ch[x][0]) f2(ch[x][0], key[x].lazy);
      if (ch[x][1]) f2(ch[x][1], key[x].lazy);
      key[x].lazy = INF;
    }
  }
  // d = 0 左旋
  void rotate(int x, int d) {
    int y = fa[x];
    pushdown(y), pushdown(x);
    ch[y][d ^ 1] = ch[x][d];
    fa[ch[x][d]] = y;
    if (fa[y]) ch[fa[y]][ch[fa[y]][1] == y] = x;
    fa[x] = fa[y];
    ch[x][d] = y;
    fa[y] = x;
    pushup(y);
  }

  void splay(int x, int goal = 0) {
    // 旋到 goal 的下面
    pushdown(x);
    while (fa[x] != goal) {
      if (fa[fa[x]] == goal)
        rotate(x, ch[fa[x]][0] == x);
      else {
        int y = fa[x];
        int d = ch[fa[y]][0] == y;
        if (ch[y][d] == x)
          rotate(x, d ^ 1);
        else
          rotate(y, d);
        rotate(x, d);
      }
    }
    pushup(x);
    if (!goal) rt = x;
  }

  // 返回第 k+1 小的节点 （有哨兵!）
  int kth(int r, int k) {
    pushdown(r);
    int t = sz[ch[r][0]] + 1;
    if (t == k) return r;
    return t > k ? kth(ch[r][0], k) : kth(ch[r][1], k - t);
  }
  // 选择区间 [l,r], key_value 为区间 [l,r] 的根节点
  void select(int l, int r) {
    splay(kth(rt, l), 0);
    splay(kth(ch[rt][1], r - l + 2), rt);
  }

  void insert(int l, int r, int p) {
    splay(kth(rt, p + 1), 0);
    splay(kth(rt, p + 2), rt);
    key_value = build(l, r, ch[rt][1]);
    pushup(ch[rt][1]), pushup(rt);
  }
  void remove(int l, int r) {
    select(l, r);
    del(key_value);
    key_value = 0;
    pushup(ch[rt][1]), pushup(rt);
  }
  void del(int u) {
    if (!u) return;
    if (ch[u][0]) del(ch[u][0]);
    stk[++top] = u;
    if (ch[u][1]) del(ch[u][1]);
  }
  void reverse(int l, int r) {
    select(l, r);
    f1(key_value);
    pushup(ch[rt][1]), pushup(rt);
  }
  void change(int l, int r, int c) {
    select(l, r);
    f2(key_value, c);
    pushup(ch[rt][1]), pushup(rt);
  }
  void get_sum(int l, int r) {
    select(l, r);
    printf("%d\n", key[key_value].sum);
  }
  void get_mxsum() { printf("%d\n", key[rt].mx); }

  // 输出树的时候记得 pushdown!
  void debug(int u) {
    pushdown(u);
    if (ch[u][0]) debug(ch[u][0]);
    printf("%d\n", key[u].val);
    if (ch[u][1]) debug(ch[u][1]);
  }
} splay;

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) scanf("%d", a + i);
  splay.init(n);
  char op[15];
  for (int i = 0, pos, tot, c; i < m; i++) {
    scanf("%s", op);
    if (op[0] == 'I') {
      scanf("%d%d", &pos, &tot);
      for (int j = 1; j <= tot; j++) scanf("%d", a + j);
      splay.insert(1, tot, pos);
    } else if (op[0] == 'D') {
      scanf("%d%d", &pos, &tot);
      splay.remove(pos, pos + tot - 1);
    } else if (op[0] == 'M' && op[2] == 'K') {
      scanf("%d%d%d", &pos, &tot, &c);
      splay.change(pos, pos + tot - 1, c);
    } else if (op[0] == 'R') {
      scanf("%d%d", &pos, &tot);
      splay.reverse(pos, pos + tot - 1);
    } else if (op[0] == 'G') {
      scanf("%d%d", &pos, &tot);
      splay.get_sum(pos, pos + tot - 1);
    } else {
      splay.get_mxsum();
    }
  }
}

/*
插入区间：
对区间先建立一棵平衡树，然后把pos转到根，把新平衡树插入到后继中。

删除区间：
select一下，删除key_value

翻转，修改区间：
select一下，打翻转/修改标记

区间求和：
维护子树和

区间最大子序列和
维护子序列最大和
*/