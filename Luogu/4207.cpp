#include <bits/stdc++.h>
using namespace std;

const int maxn = 505;
struct Point {
  double x, y;
  Point(double x = 0, double y = 0) : x(x), y(y) {}
};
struct Line {
  Point s, t;
} line[maxn];
struct Circle {
  Point c;
  double r;
} circle[maxn];

double F(double x) {}
double simpson(double a, double b) {  // 三点Simpson法
  double c = a + (b - a) / 2;
  return (F(a) + 4 * F(c) + F(b)) * (b - a) / 6;
}
double asr(double a, double b, double eps, double A) {
  //自适应Simpson公式（递归过程）。已知整个区间[a,b]上的三点Simpson值A
  double c = a + (b - a) / 2;
  double L = simpson(a, c), R = simpson(c, b);
  if (fabs(L + R - A) <= 15 * eps) return L + R + (L + R - A) / 15.0;
  return asr(a, c, eps / 2, L) + asr(c, b, eps / 2, R);
}
double asr(double a, double b, double eps) {
  return asr(a, b, eps, simpson(a, b));
}

Line getline(Circle A, Circle B) { Line ret; }

int n;
double alpha, h[maxn];
int main() {
  scanf("%d%lf", &n, &alpha);
  double s = 0;
  for (int i = 0; i <= n; i++) {
    scanf("%d", h + i);
    s += h[i];
    h[i] = s / tan(alpha);
  }
  double L = 1e9, R = -1e9;
  for (int i = 0, r; i <= n; i++) {
    if (i < n)
      scanf("%d", &r);
    else
      r = 0;
    L = min(L, h[i] - r);
    R = max(R, h[i] + r);
    circle[i] = Circle{Point(h[i], 0), r};
  }
  for (int i = 0; i < n; i++) {
    line[i] = getline(circle[i], circle[i + 1]);
  }
  printf("%.2lf\n", 2 * asr(L, R, 1e-7));
}