#include <bits/stdc++.h>
using namespace std;
#define lson (rt << 1)
#define rson (rt << 1 | 1)
const int maxn = 1e5 + 5;
struct Node {
  bool luld, luru, lurd, ldru, ldrd, rurd;
} seg[maxn << 2];
bool connect[2][maxn][2];
int n;

void pushup(Node &o, Node &ls, Node &rs, int mid) {
  o.luru = (ls.luru && connect[0][mid][0] && rs.luru) ||
           (ls.lurd && connect[1][mid][0] && rs.ldru);
  o.ldrd = (ls.ldrd && connect[1][mid][0] && rs.ldrd) ||
           (ls.ldru && connect[0][mid][0] && rs.lurd);
  o.luld = ls.luld || (ls.luru && connect[0][mid][0] && rs.luld &&
                       connect[1][mid][0] && ls.ldrd);
  o.rurd = rs.rurd || (rs.luru && connect[0][mid][0] && ls.rurd &&
                       connect[1][mid][0] && rs.ldrd);
  o.lurd = (ls.lurd && connect[1][mid][0] && rs.ldrd) ||
           (ls.luru && connect[0][mid][0] && rs.lurd);
  o.ldru = (ls.ldru && connect[0][mid][0] && rs.luru) ||
           (ls.ldrd && connect[1][mid][0] && rs.ldru);
}
void update(int l, int r, int rt, int p) {
  if (l == r) {
    Node &o = seg[rt];
    o.luld = o.rurd = o.lurd = o.ldru = connect[0][p][1];
    return;
  }
  int m = l + r >> 1;
  if (p <= m)
    update(l, m, lson, p);
  else
    update(m + 1, r, rson, p);
  pushup(seg[rt], seg[lson], seg[rson], m);
}
Node query(int l, int r, int rt, int L, int R) {
  if (L <= l && R >= r) return seg[rt];
  int m = l + r >> 1;
  if (m < L)
    return query(m + 1, r, rson, L, R);
  else if (m >= R)
    return query(l, m, lson, L, R);
  else {
    Node a = query(l, m, lson, L, R);
    Node b = query(m + 1, r, rson, L, R);
    Node ret;
    pushup(ret, a, b, m);
    return ret;
  }
}
void build(int l, int r, int rt) {
  if (l == r) {
    seg[rt].lurd = seg[rt].luld = seg[rt].rurd = seg[rt].ldru = 0;
    seg[rt].luru = seg[rt].ldrd = 1;
    return;
  }
  int m = l + r >> 1;
  build(l, m, lson);
  build(m + 1, r, rson);
  pushup(seg[rt], seg[lson], seg[rson], m);
}

bool ask(int r1, int c1, int r2, int c2) {
  if (c1 > c2) swap(r1, r2), swap(c1, c2);
  Node o = query(1, n, 1, c1, c2);
  Node l = query(1, n, 1, 1, c1);
  Node r = query(1, n, 1, c2, n);
  if (r1 == 0 && r2 == 0)
    return (o.luru || (l.rurd && o.ldru) || (r.luld && o.lurd) ||
            (l.rurd && o.ldrd && r.luld));
  if (r1 == 0 && r2 == 1)
    return (o.lurd || (l.rurd && o.ldrd) || (r.luld && o.luru) ||
            (l.rurd && o.ldru && r.luld));
  if (r1 == 1 && r2 == 0)
    return (o.ldru || (l.rurd && o.luru) || (r.luld && o.ldrd) ||
            (l.rurd && o.lurd && r.luld));
  if (r1 == 1 && r2 == 1)
    return (o.ldrd || (l.rurd && o.lurd) || (r.luld && o.ldru) ||
            (l.rurd && o.luru && r.luld));
}
int main() {
  scanf("%d", &n);
  build(1, n, 1);
  char op[20];
  while (scanf("%s", op)) {
    if (op[0] == 'E') break;
    int r1, c1, r2, c2;
    scanf("%d%d%d%d", &r1, &c1, &r2, &c2);
    r1--, r2--;
    if (op[0] == 'O' || op[0] == 'C') {
      if (r1 == r2) {
        connect[r1][min(c1, c2)][0] = op[0] == 'O';
        update(1, n, 1, c1);
        update(1, n, 1, c2);
      } else {
        connect[0][c1][1] = op[0] == 'O';
        update(1, n, 1, c1);
      }
    } else {
      if (ask(r1, c1, r2, c2))
        puts("Y");
      else
        puts("N");
    }
  }
}
/*
并查集不支持在线删边

线段树维护区间[l,r]的四个端点的连通性
*/