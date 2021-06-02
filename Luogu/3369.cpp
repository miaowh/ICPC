#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 5;
struct Splay {
  int sz[maxn], ch[maxn][2], fa[maxn];
  int key[maxn], cnt[maxn];
  int rt, top, tot;
  int stk[maxn];  // 模拟内存

  // 判断x是其父亲的哪个节点
  inline int son(int x) { return x == ch[fa[x]][1]; }
  void init() {
    rt = top = tot = 0;
    ch[rt][0] = ch[rt][1] = 0;
    cnt[rt] = sz[rt] = fa[rt] = 0;
  }

  void rotate(int x) {
    int y = fa[x], z = fa[y], chk = son(x);
    ch[y][chk] = ch[x][chk ^ 1];
    fa[ch[x][chk ^ 1]] = y;
    ch[x][chk ^ 1] = y;
    fa[y] = x;
    fa[x] = z;
    if (z) ch[z][y == ch[z][1]] = x;  // !
    pushup(y), pushup(x);
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

  // 查询第k小的节点。 1-index
  int kth(int k) {
    for (int p = rt;;) {
      if (ch[p][0] && k <= sz[ch[p][0]])
        p = ch[p][0];
      else {
        k -= cnt[p] + sz[ch[p][0]];
        if (k <= 0) {
          splay(p);  // 外部单独调用需要splay，其它情况不需要。
          return p;
        }
        p = ch[p][1];
      }
    }
  }

  // 查询值为val的节点是第几小的。 1-index
  int rank(int val) {
    int ret = 0;
    for (int p = rt;;) {
      if (val < key[p])
        p = ch[p][0];
      else {
        ret += sz[ch[p][0]];
        if (val == key[p]) {
          splay(p);
          return ret + 1;
        }
        ret += cnt[p];
        p = ch[p][1];
      }
    }
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

  // 删除值为val的节点
  void remove(int val) {
    rank(val);
    if (cnt[rt] > 1) {
      cnt[rt]--;
      pushup(rt);
      return;
    }
    stk[++top] = rt;
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
} splay;

int main() {
  int n;
  scanf("%d", &n);
  splay.init();
  for (int i = 0, op, x; i < n; i++) {
    scanf("%d%d", &op, &x);
    if (op == 1) {
      splay.insert(x);
    } else if (op == 2) {
      splay.remove(x);
    } else if (op == 3) {
      printf("%d\n", splay.rank(x));
    } else if (op == 4) {
      printf("%d\n", splay.key[splay.kth(x)]);
    } else if (op == 5) {
      splay.insert(x);
      printf("%d\n", splay.key[splay.pre()]);
      splay.remove(x);
    } else {
      splay.insert(x);
      printf("%d\n", splay.key[splay.nxt()]);
      splay.remove(x);
    }
  }
}