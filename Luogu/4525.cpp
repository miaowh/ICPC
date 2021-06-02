#include <bits/stdc++.h>
using namespace std;
const double eps = 1e-6;
double a, b, c, d, L, R;

double F(double x) { return (c * x + d) / (a * x + b); }
double simpson(double a, double b) {  // 三点Simpson法
  double c = a + (b - a) / 2;
  return (F(a) + 4 * F(c) + F(b)) * (b - a) / 6;
}
double asr(
    double a, double b, double eps,
    double
        A) {  //自适应Simpson公式（递归过程）。已知整个区间[a,b]上的三点Simpson值A
  double c = a + (b - a) / 2;
  double L = simpson(a, c), R = simpson(c, b);
  if (fabs(L + R - A) <= 15 * eps) return L + R + (L + R - A) / 15.0;
  return asr(a, c, eps / 2, L) + asr(c, b, eps / 2, R);
}
double asr(double a, double b, double eps) {
  return asr(a, b, eps, simpson(a, b));
}

int main() {
  scanf("%lf%lf%lf%lf%lf%lf", &a, &b, &c, &d, &L, &R);
  printf("%.6lf\n", asr(L, R, eps));
}