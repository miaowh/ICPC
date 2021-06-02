#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Point {
  int x, y;
  bool operator<(const Point &a) const {
    if (x == a.x) return y < a.y;
    return x < a.x;
  }
};
Point operator-(Point a, Point b) { return Point{a.x - b.x, a.y - b.y}; }
ll Cross(Point A, Point B) { return 1LL * A.x * B.y - 1LL * A.y * B.x; }

vector<Point> ConvexHull(vector<Point> ps) {
  int n = ps.size(), k = 0;
  if (n <= 1) return ps;
  sort(ps.begin(), ps.end());
  vector<Point> ret(n * 2);
  for (int i = 0; i < n; ret[k++] = ps[i++])
    while (k > 1 && Cross(ret[k - 1] - ret[k - 2], ps[i] - ret[k - 2]) < 0) --k;
  for (int i = n - 2, t = k; i >= 0; ret[k++] = ps[i--])
    while (k > t && Cross(ret[k - 1] - ret[k - 2], ps[i] - ret[k - 2]) <= 0)
      --k;
  ret.resize(k - 1);
  return ret;
}

const int maxn = 105;
Point a[maxn], b[maxn];
inline ll sqr(ll x) { return x * x; }
inline double dis(const Point &a, const Point &b) {
  return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
}
int main() {
  int n;
  while (~scanf("%d", &n)) {
    if (!n) break;
    vector<Point> ps;
    for (int i = 0, x, y; i < n; i++) {
      scanf("%d%d", &x, &y);
      ps.push_back({x, y});
    }
    auto b = ConvexHull(ps);
    double ans = 0;
    if (b.size() > 2) b.push_back(b[0]);
    for (int i = 0; i < b.size() - 1; i++) ans += dis(b[i], b[i + 1]);
    printf("%.2f\n", ans);
  }
}