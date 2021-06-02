#include <bits/stdc++.h>
using namespace std;
const double eps = 1e-7;
double a;

double F(double x) { return pow(x, a / x - x); }
double simpson(double a, double b) {  // 三点Simpson法
  double c = a + (b - a) / 2;
  return (F(a) + 4 * F(c) + F(b)) * (b - a) / 6;
}
//自适应Simpson公式（递归过程）。已知整个区间[a,b]上的三点Simpson值A
double asr(double a, double b, double eps, double A) {
  double c = a + (b - a) / 2;
  double L = simpson(a, c), R = simpson(c, b);
  if (fabs(L + R - A) <= 15 * eps) return L + R + (L + R - A) / 15.0;
  return asr(a, c, eps / 2, L) + asr(c, b, eps / 2, R);
}
double asr(double a, double b, double eps) {
  return asr(a, b, eps, simpson(a, b));
}

int main() {
  scanf("%lf", &a);
  if (a < 0)
    puts("orz");
  else
    printf("%.5lf\n", asr(1e-10, 30.0, eps));
}