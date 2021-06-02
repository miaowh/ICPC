#include <bits/stdc++.h>
using namespace std;

using db = double;
const db eps = 1e-8;       //精度系数
const db PI = acos(-1.0);  //π
const int N = 4;
inline int sign(db a) { return a < -eps ? -1 : a > eps; }
inline int cmp(db a, db b) { return sign(a - b); }
struct Point {
  db x, y;
  Point(db x = 0, db y = 0) : x(x), y(y) {}
  const bool operator<(Point A) const { return x == A.x ? y < A.y : x < A.x; }
};
typedef Point Vector;

Vector operator+(Vector A, Vector B) { return Vector(A.x + B.x, A.y + B.y); }
Vector operator-(Vector A, Vector B) { return Vector(A.x - B.x, A.y - B.y); }
Vector operator*(Vector A, db p) { return Vector(A.x * p, A.y * p); }
Vector operator/(Vector A, db p) { return Vector(A.x / p, A.y / p); }

db Dot(Vector A, Vector B) { return A.x * B.x + A.y * B.y; }    //向量点乘
db Length(Vector A) { return sqrt(Dot(A, A)); }                 //向量长度
db Cross(Vector A, Vector B) { return A.x * B.y - A.y * B.x; }  //向量叉乘

struct Line {
  Point u;
  Vector v;
  Line() {}
  Line(Point u, Vector v) : u(u), v(v) {}
  void unit() {
    db len = Length(v);
    v.x /= len, v.y /= len;
  }
};

//点在直线上投影
Point GetLineProjection(Point P, Line line) {
  return line.u + line.v * (Dot(line.v, P - line.u) / Dot(line.v, line.v));
}

struct Circle {
  Point c;
  db r;
  Circle() : c(Point(0, 0)), r(0) {}
  Circle(Point c, db r = 0) : c(c), r(r) {}
  Point point(db a) { return Point(c.x + cos(a) * r, c.y + sin(a) * r); }
};

// a[i] 和 b[i] 分别是第i条切线在圆A和圆B上的切点
int getTangents(Circle A, Circle B, Point* a, Point* b) {
  int cnt = 0;
  if (A.r < B.r) {
    swap(A, B);
    swap(a, b);
  }
  db d2 = (A.c.x - B.c.x) * (A.c.x - B.c.x) + (A.c.y - B.c.y) * (A.c.y - B.c.y);
  db rdiff = A.r - B.r;
  db rsum = A.r + B.r;
  if (sign(d2 - rdiff * rdiff) < 0) return 0;  //内含

  db base = atan2(B.c.y - A.c.y, B.c.x - A.c.x);
  if (sign(d2) == 0 && sign(A.r - B.r) == 0) return -1;  //无限多条切线
  if (sign(d2 - rdiff * rdiff) == 0) {                   //内切，一条切线
    a[cnt] = A.point(base);
    b[cnt] = B.point(base);
    ++cnt;
    return 1;
  }
  //有外公切线
  db ang = acos(rdiff / sqrt(d2));
  a[cnt] = A.point(base + ang);
  b[cnt] = B.point(base + ang);
  ++cnt;
  a[cnt] = A.point(base - ang);
  b[cnt] = B.point(base - ang);
  ++cnt;
  if (sign(d2 - rsum * rsum) == 0) {  //一条内公切线
    a[cnt] = A.point(base);
    b[cnt] = B.point(PI + base);
    ++cnt;
  } else if (sign(d2 - rsum * rsum) > 0) {  //两条内公切线
    db ang = acos(rsum / sqrt(d2));
    a[cnt] = A.point(base + ang);
    b[cnt] = B.point(PI + base + ang);
    ++cnt;
    a[cnt] = A.point(base - ang);
    b[cnt] = B.point(PI + base - ang);
    ++cnt;
  }
  return cnt;
}  // 两圆公切线 返回切线的条数，-1表示无穷多条切线

// 不过圆心O的圆A，反演后得到的圆
Circle Inversion_C2C(Point O, db R, Circle A) {
  db oa = Length(A.c - O);
  db br = R * R * A.r / (oa * oa - A.r * A.r);
  db ob = oa * br / A.r;
  db bx = O.x + (A.c.x - O.x) * ob / oa;
  db by = O.y + (A.c.y - O.y) * ob / oa;
  return Circle(Point(bx, by), br);
}

Circle Inversion_L2C(Point O, db R, Line line) {
  Point p = GetLineProjection(O, line);
  db d = Length(O - p);
  db br = R * R / (2 * d);
  Vector bv = (p - O) / d * br;
  return Circle(O + bv, br);
}

bool theSameSideOfLine(Point A, Point B, Line line) {
  return sign(Cross(A - line.u, line.v)) * sign(Cross(B - line.u, line.v)) > 0;
}  // 返回 true 如果 A B 两点在直线同侧

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    Circle A, B;
    Point P;
    scanf("%lf%lf%lf", &A.c.x, &A.c.y, &A.r);
    scanf("%lf%lf%lf", &B.c.x, &B.c.y, &B.r);
    scanf("%lf%lf", &P.x, &P.y);
    Circle NA = Inversion_C2C(P, 10, A);
    Circle NB = Inversion_C2C(P, 10, B);
    Point LA[N], LB[N];
    Circle ansC[N];
    int q = getTangents(NA, NB, LA, LB), ans = 0;
    for (int i = 0; i < q; ++i)
      if (theSameSideOfLine(NA.c, NB.c, Line(LA[i], LB[i] - LA[i]))) {
        if (!theSameSideOfLine(P, NA.c, Line(LA[i], LB[i] - LA[i]))) continue;
        ansC[ans++] = Inversion_L2C(P, 10, Line(LA[i], LB[i] - LA[i]));
      }
    printf("%d\n", ans);
    for (int i = 0; i < ans; ++i) {
      printf("%.8f %.8f %.8f\n", ansC[i].c.x, ansC[i].c.y, ansC[i].r);
    }
  }

  return 0;
}