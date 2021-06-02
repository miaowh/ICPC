// #include <bits/stdc++.h>
#include <assert.h>
#include <cstdio>
#include <vector>
using namespace std;
const int maxn = 2e5 + 5;

/*
sz[0]
ch[0][0]
ch[0][1]
*/
struct Splay {
  int sz[maxn], ch[maxn][2], fa[maxn];
  int key[maxn], cnt[maxn];
  int rt, top, tot, id;
  int stk[maxn];  // 模拟内存

  // 判断x是其父亲的哪个节点
  inline int son(int x) { return x == ch[fa[x]][1]; }
  inline void init() {
    rt = top = tot = 0;
    ch[rt][0] = ch[rt][1] = 0;
    cnt[rt] = sz[rt] = fa[rt] = 0;
    id = 0;
  }

  inline void rotate(int x) {
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
  inline void splay(int x, int goal = 0) {
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

  inline int newnode(int p = 0, int k = 0, int c = 0) {
    int x = top ? stk[top--] : ++tot;
    if (p) ch[p][c] = x;  // !
    fa[x] = p, sz[x] = 1, key[x] = k, cnt[x] = 1;
    ch[x][0] = ch[x][1] = 0;
    return x;
  }
  inline void pushup(int x) {
    if (!x) return;
    sz[x] = cnt[x];
    if (ch[x][0]) sz[x] += sz[ch[x][0]];
    if (ch[x][1]) sz[x] += sz[ch[x][1]];
  }

  inline int kth(int k) {
    for (int p = rt; p;) {
      if (ch[p][0] && k <= sz[ch[p][0]])
        p = ch[p][0];
      else {
        k -= cnt[p] + (ch[p][0] ? sz[ch[p][0]] : 0);
        if (k <= 0) {
          // 外部单独调用需要splay，其它情况如果不想改变树的形状就不要splay。
          splay(p);
          return p;
        }
        p = ch[p][1];
      }
    }
    assert(false);
  }
  inline void insert(int k, int val) {
    if (!rt) {
      rt = newnode(0, val);
      return;
    }
    if (!k) {
      int x = newnode(0, val);
      ch[x][1] = rt;
      fa[rt] = x;
      rt = x;
      pushup(x);
      return;
    }
    kth(k);
    int rson = ch[rt][1];
    int x = newnode(rt, val, 1);
    if (!rson) {
      ch[rt][1] = x;
      fa[x] = rt;
      pushup(x), pushup(rt);
      // splay(x);
      return;
    }
    fa[rson] = x;
    ch[x][1] = rson;
    pushup(x);
    pushup(rt);
    splay(x);
  }

  int ans[maxn];
  void dfs(int u) {
    if (ch[u][0]) dfs(ch[u][0]);
    ans[++id] = key[u];
    if (ch[u][1]) dfs(ch[u][1]);
  }
} splay;

int val[maxn], pos[maxn];
int main() {
  int n;
  while (~scanf("%d", &n)) {
    for (int i = 1; i <= n; i++) scanf("%d%d", &pos[i], &val[i]);
    splay.init();
    for (int i = 1; i <= n; i++) {
      splay.insert(pos[i], val[i]);
    }
    splay.dfs(splay.rt);
    for (int i = 1; i <= n; i++)
      printf("%d%c", splay.ans[i], i == n ? '\n' : ' ');
  }
}