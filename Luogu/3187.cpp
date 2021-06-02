#include <bits/stdc++.h>
using namespace std;
const double eps = 1e-12;
struct Point {
  double x, y;
  bool operator<(const Point& a) const {
    if (x == a.x) return y < a.y;
    return x < a.x;
  }
};
Point operator-(Point a, Point b) { return Point{a.x - b.x, a.y - b.y}; }
Point operator+(Point a, Point b) { return Point{a.x + b.x, a.y + b.y}; }
Point operator*(Point a, double b) { return Point{a.x * b, a.y * b}; }
double Cross(Point A, Point B) { return A.x * B.y - A.y * B.x; }
double Cross(Point A, Point B, Point C) { return Cross(B - A, C - A); }
double Dot(Point A, Point B) { return A.x * B.x + A.y * B.y; }
double Dot(Point A, Point B, Point C) { return Dot(B - A, C - A); }
double sqr(double x) { return x * x; }
double dis(Point A, Point B) { return sqrt(sqr(A.x - B.x) + sqr(A.y - B.y)); }

int dcmp(double x) {
  if (fabs(x) < eps)
    return 0;
  else
    return x > 0 ? 1 : -1;
}

vector<Point> ConvexHull(vector<Point> ps) {
  int n = ps.size(), k = 0;
  if (n <= 1) return ps;
  sort(ps.begin(), ps.end());
  vector<Point> ret(n * 2);
  for (int i = 0; i < n; ret[k++] = ps[i++])
    while (k > 1 && dcmp(Cross(ret[k - 2], ret[k - 1], ps[i])) <= 0) --k;
  for (int i = n - 2, t = k; ~i; ret[k++] = ps[i--])
    while (k > t && dcmp(Cross(ret[k - 2], ret[k - 1], ps[i])) <= 0) --k;
  ret.resize(k - 1);
  return ret;
}

vector<Point> work(vector<Point> ps) {
  ps.push_back(ps[0]);
  int n = ps.size();
  vector<Point> ret(4);
  double res = 1e18;

  for (int i = 0, j = 2, k = 2, t = 2; i < n - 1; i++) {
    while (dcmp(Dot(ps[i], ps[i + 1], ps[j]) -
                Dot(ps[i], ps[i + 1], ps[j + 1])) <= 0)
      (++j) %= (n - 1);
    while (dcmp(Cross(ps[i], ps[i + 1], ps[k]) -
                Cross(ps[i], ps[i + 1], ps[k + 1])) <= 0)
      (++k) %= (n - 1);
    while (dcmp(Dot(ps[i], ps[i + 1], ps[t]) -
                Dot(ps[i], ps[i + 1], ps[t + 1])) >= 0)
      (++t) %= (n - 1);

    double ab = dis(ps[i], ps[i + 1]);
    double hei = Cross(ps[i], ps[i + 1], ps[k]) / ab;
    double l = fabs(Dot(ps[i], ps[i + 1], ps[j])) / ab;
    double r = fabs(Dot(ps[i], ps[i + 1], ps[t])) / ab;
    double wide = l + r;
    if (hei * wide < res) {
      res = hei * wide;
      ret[0] = ps[i] + (ps[i + 1] - ps[i]) * (l / ab);
      ret[1] = ret[0] + (ps[j] - ret[0]) * (hei / dis(ret[0], ps[j]));
      ret[2] = ret[1] + (ps[k] - ret[1]) * (wide / dis(ret[1], ps[k]));
      ret[3] = ret[2] + (ps[t] - ret[2]) * (hei / dis(ret[2], ps[t]));
    }
  }
  if (dcmp(res) <= 0) res = 0;
  printf("%.5f\n", res);
  return ret;
}
int main() {
  int n;
  scanf("%d", &n);
  double x, y;
  vector<Point> ps;
  for (int i = 0; i < n; i++) {
    scanf("%lf%lf", &x, &y);
    ps.push_back({x, y});
  }
  auto ch = ConvexHull(ps);
  auto ans = work(ch);
  int k = 0;
  for (int i = 1; i < ans.size(); i++) {
    if (dcmp(ans[k].y - ans[i].y) == 0 && ans[k].x > ans[i].x)
      k = i;
    else if (ans[k].y > ans[i].y)
      k = i;
  }
  for (int i = 0; i < 4; i++) {
    if (dcmp(ans[(i + k) % 4].x) <= 0) ans[(i + k) % 4].x = 0;
    if (dcmp(ans[(i + k) % 4].y) <= 0) ans[(i + k) % 4].y = 0;
    printf("%.5f %.5f\n", ans[(i + k) % 4].x, ans[(i + k) % 4].y);
  }
}