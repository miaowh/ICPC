#include <bits/stdc++.h>
using namespace std;

struct Point {
  int x, y;
  bool operator<(const Point &rhs) const {
    if (x == rhs.x) return y < rhs.y;
    return x < rhs.x;
  }
};
Point operator-(Point a, Point b) { return Point{a.x - b.x, a.y - b.y}; }
int Cross(Point A, Point B) { return A.x * B.y - A.y * B.x; }
int Cross(Point A, Point B, Point C) { return Cross(B - A, C - A); }
int sqr(int x) { return x * x; }
int dis(Point A, Point B) { return sqr(A.x - B.x) + sqr(A.y - B.y); }

vector<Point> ConvexHull(vector<Point> ps) {
  int n = ps.size(), k = 0;
  if (n <= 1) return ps;
  sort(ps.begin(), ps.end());
  vector<Point> ret(n * 2);
  for (int i = 0; i < n; ret[k++] = ps[i++])
    while (k > 1 && Cross(ret[k - 2], ret[k - 1], ps[i]) <= 0) --k;
  for (int i = n - 2, t = k; ~i; ret[k++] = ps[i--])
    while (k > t && Cross(ret[k - 2], ret[k - 1], ps[i]) <= 0) --k;
  ret.resize(k - 1);
  return ret;
}

int work(vector<Point> ps) {
  if (ps.size() <= 1) return 0;
  if (ps.size() == 2) return dis(ps[0], ps[1]);
  ps.push_back(ps[0]);
  int n = ps.size(), ret = 0;
  for (int i = 0, j = 2; i < n - 1; i++) {
    while (Cross(ps[i], ps[i + 1], ps[j]) <= Cross(ps[i], ps[i + 1], ps[j + 1]))
      (++j) %= (n - 1);
    ret = max({ret, dis(ps[i], ps[j]), dis(ps[i + 1], ps[j])});
  }
  return ret;
}

int main() {
  int n;
  scanf("%d", &n);
  vector<Point> ps;
  for (int i = 0, x, y; i < n; i++) {
    scanf("%d%d", &x, &y);
    ps.push_back({x, y});
  }
  auto ch = ConvexHull(ps);
  int ans = work(ch);
  printf("%d\n", ans);
}
