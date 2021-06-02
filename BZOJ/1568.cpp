#include <bits/stdc++.h>
using namespace std;
#define lson (rt << 1)
#define rson (rt << 1 | 1)
const int maxn = 1e5 + 5;

struct Node {
  double k, b;
} seg[maxn << 2];

void build(int l, int r, int rt) {
  seg[rt].b = seg[rt].k = 0;
  if (l == r) return;
  int m = l + r >> 1;
  build(l, m, lson);
  build(m + 1, r, rson);
}
double val(const Node &t, int x) { return t.k * (x - 1) + t.b; }
void update(int l, int r, int rt, Node x) {
  if (l == r) {
    if (val(seg[rt], l) < val(x, l)) seg[rt] = x;
    return;
  }
  int m = l + r >> 1;
  if (x.k > seg[rt].k) {
    if (val(x, m) <= val(seg[rt], m)) {
      update(m + 1, r, rson, x);
    } else {
      update(l, m, lson, seg[rt]);
      seg[rt] = x;
    }
  } else {
    if (val(x, m) <= val(seg[rt], m)) {
      update(l, m, lson, x);
    } else {
      update(m + 1, r, rson, seg[rt]);
      seg[rt] = x;
    }
  }
}
double query(int l, int r, int rt, int p) {
  if (l == r) return val(seg[rt], l);
  int m = l + r >> 1;
  double ans = val(seg[rt], p);
  if (p <= m)
    ans = max(ans, query(l, m, lson, p));
  else
    ans = max(ans, query(m + 1, r, rson, p));
  return ans;
}
int main() {
  int n;
  scanf("%d", &n);
  char op[20];
  build(1, maxn, 1);
  for (int i = 0; i < n; i++) {
    scanf("%s", op);
    if (op[0] == 'P') {
      double k, b;
      scanf("%lf%lf", &b, &k);
      update(1, maxn, 1, Node{k, b});
    } else {
      int x;
      scanf("%d", &x);
      printf("%d\n", int(query(1, maxn, 1, x)) / 100);
    }
  }
}
/*
二维平面上有n个操作：
1. 加入一条直线
2. 给定x值，查询所有直线对应y的最大值

实际上是在维护若干直线组成的下凸壳。
*/