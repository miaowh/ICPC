#include <bits/stdc++.h>
using namespace std;
#define lson (rt << 1)
#define rson (rt << 1 | 1)
#define Lson l, m, lson
#define Rson m + 1, r, rson
const int INF = 2147483647;
const int maxn = 5e4 + 5;
using ll = long long;
int a[maxn];
int sz[maxn * 40];  // sz[u]: 以u为根的子树的节点个数（不包括根）
int ch[maxn * 40][2];  // ch[u][0]: u的左儿子
int fa[maxn * 40];     // fa[u]: u的父亲
int key[maxn * 40];    // key[u]: u点所代表的权值
int cnt[maxn * 40];    // cnt[u]: u点的个数（multiset）
int stk[maxn * 40];    // 模拟内存
int n, m, tot;
int top;  // 栈顶

struct Splay {
  int rt;  // 根
  /*
  fa[u] = 0 表示u为根节点
  ch[u][0/1] = 0 表示没有相应的孩子
  任何时候都不应该访问到 0 这个节点
  */
  void init() {
    rt = 0;
    ch[rt][0] = ch[rt][1] = 0;
    cnt[rt] = sz[rt] = fa[rt] = 0;
  }

  /*
  p: 父亲, k: 权值
  p = 0 表示当前是根节点
  */
  int newnode(int p = 0, int k = 0) {
    int x = top ? stk[top--] : ++tot;
    if (p) ch[p][key[p] < k] = x;  // !
    fa[x] = p, sz[x] = 1, key[x] = k, cnt[x] = 1;
    ch[x][0] = ch[x][1] = 0;
    return x;
  }
  void pushup(int x) {
    if (!x) return;
    sz[x] = cnt[x];
    if (ch[x][0]) sz[x] += sz[ch[x][0]];
    if (ch[x][1]) sz[x] += sz[ch[x][1]];
  }

  // 判断x是其父亲的哪个节点
  // 单独使用请判父亲是否为 0
  int son(int x) { return x == ch[fa[x]][1]; }

  // 单独使用请判父亲是否为 0
  void rotate(int x) {
    int y = fa[x], z = fa[y], chk = son(x);
    ch[y][chk] = ch[x][chk ^ 1];
    fa[ch[x][chk ^ 1]] = y;
    ch[x][chk ^ 1] = y;
    fa[y] = x;
    fa[x] = z;
    if (z) ch[z][y == ch[z][1]] = x;  // !
    pushup(y), pushup(x);  // 对于splay操作来说，pushup(x)是多余的
  }

  // 旋到 goal 的下面
  void splay(int x, int goal = 0) {
    while (fa[x] != goal) {
      if (fa[fa[x]] == goal)
        rotate(x);
      else {
        int y = fa[x];
        int d = ch[fa[y]][0] == y;
        if (ch[y][d] == x)
          rotate(x);
        else
          rotate(y);
        rotate(x);
      }
    }
    pushup(x);
    if (!goal) rt = x;
  }

  // 查询第k小的节点。 1-index
  int kth(int k) {
    for (int p = rt; p;) {
      if (ch[p][0] && k <= sz[ch[p][0]])
        p = ch[p][0];
      else {
        k -= cnt[p];
        if (ch[p][0]) k -= sz[ch[p][0]];
        if (k <= 0) {
          // 如果不想改变树的形状就不要splay。
          splay(p);
          return p;
        }
        p = ch[p][1];
      }
    }
    return -1;
  }

  // 查询值为val的节点是第几小的。 1-index
  // [1,2,2,3]: rank(2) = 2, rank(3) = 4
  int rank(int val) {
    int ret = 0;
    for (int p = rt; p;) {
      if (val < key[p])
        p = ch[p][0];
      else {
        if (ch[p][0]) ret += sz[ch[p][0]];
        if (val == key[p]) {
          splay(p);
          return ret + 1;
        }
        ret += cnt[p];
        p = ch[p][1];
      }
    }
    return 0;
  }

  // 插入值为val的节点
  void insert(int val) {
    for (int p = rt, f = 0;;) {
      if (!p) {
        int x = newnode(f, val);
        pushup(x), pushup(f);
        splay(x);
        break;
      }
      if (key[p] == val) {
        cnt[p]++;
        pushup(p), pushup(f);
        splay(p);
        break;
      }
      f = p;
      p = ch[p][key[p] < val];
    }
  }

  // 前驱节点
  int pre() {
    int p = ch[rt][0];
    while (ch[p][1]) p = ch[p][1];
    return p;
  }
  // 后继节点
  int nxt() {
    int p = ch[rt][1];
    while (ch[p][0]) p = ch[p][0];
    return p;
  }
  void remove(int val) {
    rank(val);  // 将val旋转到根
    if (cnt[rt] > 1) {
      cnt[rt]--;
      pushup(rt);
      return;
    }
    stk[++top] = rt;  // 内存回收
    if (!ch[rt][0] && !ch[rt][1]) {
      rt = 0;
      return;
    }
    if (!ch[rt][0]) {
      rt = ch[rt][1];
      fa[rt] = 0;
      return;
    }
    if (!ch[rt][1]) {
      rt = ch[rt][0];
      fa[rt] = 0;
      return;
    }
    int x = pre(), p = rt;
    splay(x);
    fa[ch[p][1]] = x;
    ch[x][1] = ch[p][1];
    pushup(rt);
  }
};

struct SegTree {
  Splay seg[maxn << 2];
  void build(int l, int r, int rt) {
    seg[rt].init();
    for (int i = l; i <= r; i++) seg[rt].insert(a[i]);
    if (l == r) return;
    int m = l + r >> 1;
    build(Lson), build(Rson);
  }
  void update(int l, int r, int rt, int p, int x) {
    seg[rt].remove(a[p]);
    seg[rt].insert(x);
    if (l == r) return;
    int m = l + r >> 1;
    if (p <= m)
      update(Lson, p, x);
    else
      update(Rson, p, x);
  }
  int queryRank(int l, int r, int rt, int L, int R, int x) {
    if (L <= l && R >= r) {
      seg[rt].insert(x);
      int ret = seg[rt].rank(x) - 1;
      seg[rt].remove(x);
      return ret;
    }
    int m = l + r >> 1, ret = 0;
    if (L <= m) ret += queryRank(Lson, L, R, x);
    if (m + 1 <= R) ret += queryRank(Rson, L, R, x);
    return ret;
  }
  int queryVal(int L, int R, int k) {
    int l = 0, r = 1e8, ret;
    while (l <= r) {
      int mid = l + r >> 1;
      int tmp = queryRank(1, n, 1, L, R, mid) + 1;
      if (tmp <= k)
        l = mid + 1, ret = mid;
      else
        r = mid - 1;
    }
    return ret;
  }
  int succ(int l, int r, int rt, int L, int R, int x) {
    if (L <= l && R >= r) {
      seg[rt].insert(x);
      int id = seg[rt].pre();
      seg[rt].remove(x);
      if (!id) return -INF;
      return key[id];
    }
    int m = l + r >> 1, ret = -INF;
    if (L <= m) ret = max(ret, succ(Lson, L, R, x));
    if (m + 1 <= R) ret = max(ret, succ(Rson, L, R, x));
    return ret;
  }
  int nxt(int l, int r, int rt, int L, int R, int x) {
    if (L <= l && R >= r) {
      seg[rt].insert(x);
      int id = seg[rt].nxt();
      seg[rt].remove(x);
      if (!id) return INF;
      return key[id];
    }
    int m = l + r >> 1, ret = INF;
    if (L <= m) ret = min(ret, nxt(Lson, L, R, x));
    if (m + 1 <= R) ret = min(ret, nxt(Rson, L, R, x));
    return ret;
  }

} tree;

int main() {
  // freopen("testdata.in", "r", stdin);
  // freopen("1.out", "w", stdout);

  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) scanf("%d", a + i);
  tree.build(1, n, 1);
  int op, l, r, k;
  while (m--) {
    scanf("%d%d%d", &op, &l, &r);
    if (op == 3) {
      tree.update(1, n, 1, l, r);
      a[l] = r;
    } else {
      scanf("%d", &k);
      switch (op) {
        case 1:
          printf("%d\n", tree.queryRank(1, n, 1, l, r, k) + 1);
          break;
        case 2:
          printf("%d\n", tree.queryVal(l, r, k));
          break;
        case 4:
          printf("%d\n", tree.succ(1, n, 1, l, r, k));
          break;
        case 5:
          printf("%d\n", tree.nxt(1, n, 1, l, r, k));
          break;
      }
    }
  }
}