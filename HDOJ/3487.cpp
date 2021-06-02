#include <bits/stdc++.h>
using namespace std;
const int maxn = 3e5 + 5;

#define key_value ch[ch[root][1]][0]
struct Splay {
  int a[maxn];  // a[i]: 区间i位置所对应的值
  int sz[maxn], ch[maxn][2], fa[maxn];
  int key[maxn];
  int root, tot;
  int stk[maxn], top;
  int rev[maxn];  // 区间翻转标记

  // 1-index
  void init(int n) {
    tot = top = 0;
    for (int i = 1; i <= n; i++) a[i] = i;
    // 首尾插入两个元素！！！
    root = newnode(0, -1);
    ch[root][1] = newnode(root, -1);
    key_value = build(1, n, ch[root][1]);
    pushup(ch[root][1]), pushup(root);
  }

  int build(int l, int r, int p) {
    if (l > r) return 0;
    int m = l + r >> 1;
    int x = newnode(p, a[m]);  // a[i]
    ch[x][0] = build(l, m - 1, x);
    ch[x][1] = build(m + 1, r, x);
    pushup(x);
    return x;
  }

  int newnode(int p = 0, int k = 0) {
    int x = top ? stk[top--] : ++tot;
    fa[x] = p, sz[x] = 1, key[x] = k;
    ch[x][0] = ch[x][1] = 0;
    rev[x] = 0;  // 清空反转标记
    return x;
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
    if (!goal) root = x;
  }

  // 返回第k+1小的节点 （有哨兵）
  int kth(int r, int k) {
    pushdown(r);
    int t = sz[ch[r][0]] + 1;
    if (t == k) return r;
    return t > k ? kth(ch[r][0], k) : kth(ch[r][1], k - t);
  }

  // 选择区间[l,r]
  void select(int l, int r) {
    splay(kth(root, l), 0);
    splay(kth(ch[root][1], r - l + 2), root);
  }

  void pushup(int x) {
    sz[x] = 1;
    if (ch[x][0]) sz[x] += sz[ch[x][0]];
    if (ch[x][1]) sz[x] += sz[ch[x][1]];
  }

  void pushdown(int x) {
    if (!rev[x]) return;
    swap(ch[x][0], ch[x][1]);
    if (ch[x][0]) rev[ch[x][0]] ^= 1;
    if (ch[x][1]) rev[ch[x][1]] ^= 1;
    rev[x] = 0;
  }

  // 后继节点
  int nxt() {
    pushdown(root);  // 记得 pushdown
    int p = ch[root][1];
    pushdown(p);
    while (ch[p][0]) {
      p = ch[p][0];
      pushdown(p);
    }
    return p;
  }

  // 反转区间 [l,r]
  void reverse(int l, int r) {
    select(l, r);
    rev[key_value] ^= 1;
  }
  // 将区间[l,r]切下，移动到p后面。
  void cut(int l, int r, int p) {
    select(l, r);
    int tmp = key_value;
    fa[tmp] = 0;
    key_value = 0;

    pushup(ch[root][1]), pushup(root);
    splay(kth(root, p + 1));
    int succ = nxt();
    ch[succ][0] = tmp;
    fa[tmp] = succ;
    pushup(succ);
    splay(succ);
  }

  vector<int> ans;
  void print(int u) {
    pushdown(u);  // !
    if (ch[u][0]) print(ch[u][0]);
    ans.push_back(key[u]);
    if (ch[u][1]) print(ch[u][1]);
  }

} splay;

int main() {
  int n, m;
  while (~scanf("%d%d", &n, &m)) {
    if (n < 0 && m < 0) break;
    splay.init(n);
    char op[10];
    int a, b, c;
    while (m--) {
      scanf("%s", op);
      if (op[0] == 'C') {
        scanf("%d%d%d", &a, &b, &c);
        splay.cut(a, b, c);
      } else {
        scanf("%d%d", &a, &b);
        splay.reverse(a, b);
      }
    }
    splay.ans.clear();
    splay.print(splay.root);
    for (int i = 1; i <= n; i++)
      printf("%d%c", splay.ans[i], i == n ? '\n' : ' ');
  }
}