#include <bits/stdc++.h>
using namespace std;
#define lson (rt << 1)
#define rson (rt << 1 | 1)
#define Lson l, m, lson
#define Rson m + 1, r, rson
const int maxn = 2e5 + 5;
typedef long long ll;
struct Point {
  ll x, y;
  Point(ll x = 0, ll y = 0) : x(x), y(y) {}
  bool operator<(const Point &a) const {
    if (x == a.x) return y < a.y;
    return x < a.x;
  }
};
Point operator-(Point a, Point b) { return Point(a.x - b.x, a.y - b.y); }
ll Cross(Point A, Point B) { return A.x * B.y - A.y * B.x; }
ll Cross(Point A, Point B, Point C) { return Cross(B - A, C - A); }
ll dot(Point A, Point B) { return A.x * B.x + A.y * B.y; }

vector<Point> seg[maxn << 2];
ll ans;

struct Vector {
  int x, y, id;
  int in, out;
  Vector(int x = 0, int y = 0, int id = 0, int in = 0, int out = 0)
      : x(x), y(y), id(id), in(in), out(out) {}
};
struct Query {
  int x, y, id;
  Query(int x = 0, int y = 0, int id = 0) : x(x), y(y), id(id) {}
};
vector<Vector> vec;
vector<Query> query;

void build(int l, int r, int rt) {
  int n = seg[rt].size(), k = 0;
  sort(seg[rt].begin(), seg[rt].end());
  vector<Point> tmp(2 * n);
  for (int i = 0; i < n; tmp[k++] = seg[rt][i++])
    while (k > 1 && Cross(tmp[k - 2], tmp[k - 1], seg[rt][i]) >= 0) --k;
  tmp.resize(k);
  seg[rt] = tmp;
  if (l == r) return;
  int m = l + r >> 1;
  build(Lson);
  build(Rson);
}
void update(int l, int r, int rt, int L, int R, int x, int y) {
  if (L <= l && R >= r) {
    seg[rt].push_back(Point(x, y));
    return;
  }
  int m = l + r >> 1;
  if (L <= m) update(Lson, L, R, x, y);
  if (m + 1 <= R) update(Rson, L, R, x, y);
}

void find(int rt, Point p) {
  int l = 0, r = seg[rt].size() - 1;
  int m1, m2;
  while (r - l >= 3) {
    m1 = l + (r - l) / 3, m2 = r - (r - l) / 3;
    if (dot(seg[rt][m1], p) > dot(seg[rt][m2], p))
      r = m2;
    else
      l = m1;
  }
  for (int i = l; i <= r; i++) ans = max(ans, dot(seg[rt][i], p));
}
void ask(int l, int r, int rt, int p, int x, int y) {
  if (seg[rt].size() > 0) find(rt, Point(x, y));
  if (l == r) return;
  int m = l + r >> 1;
  if (p <= m)
    ask(Lson, p, x, y);
  else
    ask(Rson, p, x, y);
}
int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0, op, x, y, id; i < n; i++) {
    scanf("%d", &op);
    if (op == 1) {
      scanf("%d%d", &x, &y);
      int m = vec.size();
      vec.push_back(Vector(x, y, m + 1, i + 1, n));
    } else if (op == 2) {
      scanf("%d", &id);
      vec[id - 1].out = i + 1;
    } else {
      scanf("%d%d", &x, &y);
      query.push_back(Query(x, y, i + 1));
    }
  }
  for (int i = 0; i < vec.size(); i++) {
    Vector &v = vec[i];
    update(1, n, 1, v.in, v.out, v.x, v.y);
  }

  build(1, n, 1);
  for (int i = 0; i < query.size(); i++) {
    Query &q = query[i];
    ans = 0;
    ask(1, n, 1, q.id, q.x, q.y);
    printf("%lld\n", ans);
  }
}