#include <bits/stdc++.h>
using namespace std;
using db = double;
const db eps = 1e-9;
const db PI = acos(-1.0);
inline int sign(db a) { return a < -eps ? -1 : a > eps; }
inline int cmp(db a, db b) { return sign(a - b); }

struct Point {
  db x, y;
  Point(db x = 0, db y = 0) : x(x), y(y) {}

  bool operator<(const Point& rhs) const {
    int s = cmp(x, rhs.x);
    if (s) return s == -1;
    return cmp(y, rhs.y) == -1;
  }
  bool operator==(const Point& rhs) const {
    return cmp(x, rhs.x) == 0 && cmp(y, rhs.y) == 0;
  }

  void print() { cerr << "Point : " << x << ' ' << y << endl; }
};
typedef Point Vector;

Vector operator+(Vector A, Vector B) { return Vector(A.x + B.x, A.y + B.y); }
Vector operator-(Vector A, Vector B) { return Vector(A.x - B.x, A.y - B.y); }
Vector operator*(Vector A, db p) { return Vector(A.x * p, A.y * p); }
Vector operator/(Vector A, db p) { return Vector(A.x / p, A.y / p); }

db Dot(Vector A, Vector B) { return A.x * B.x + A.y * B.y; }
db Length(Vector A) { return sqrt(Dot(A, A)); }
db Length2(Vector A) { return Dot(A, A); }
db Cross(Vector A, Vector B) { return A.x * B.y - A.y * B.x; }
Vector unit(Vector A) {
  db len = Length(A);
  return A / len;
}

struct Circle {
  Point c;
  db r;
  Circle() : c(Point(0, 0)), r(0) {}
  Circle(Point c, db r = 0) : c(c), r(r) {}

  // 根据角度a，返回圆上一点
  Point point(db a) { return Point(c.x + cos(a) * r, c.y + sin(a) * r); }
};

struct Line {
  Point u;
  Vector v;
  Line() {}
  Line(Point u, Vector v) : u(u), v(v) {}
};
//点在直线上投影
Point GetLineProjection(Point P, Line line) {
  return line.u + line.v * (Dot(line.v, P - line.u) / Dot(line.v, line.v));
}

Point Inversion_P2P(Point O, db R, Point A) {
  if (A == O) return A;  // 因为本题的特殊性，可以这么写s
  Vector v = A - O;
  db len = Length(v);
  db ob = R * R / len;
  return O + v * (ob / len);
}

vector<Point> CircleXLine(Circle O, Line l) {
  Point k = GetLineProjection(O.c, l);
  db d = O.r * O.r - Length2(k - O.c);
  if (sign(d) == -1) return {};
  if (sign(d) == 0) return {k};
  Point del = unit(l.v) * sqrt(d);
  return {k - del, k + del};
}

// 经过a点，与向量v垂直的垂线
Line Perpendicular(Point a, Vector v) {
  if (sign(v.y) == 0)
    return {a, Point(0, 1)};
  else {
    Point u = Point(0, v.x * a.x / v.y + a.y);
    return {a, u - a};
  }
}
// 垂直平分线
Line PerpendicularBisector(Point a, Point b) {
  Point m = (a + b) / 2;
  return Perpendicular(m, b - a);
}

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    db r;
    Point p, q;
    scanf("%lf%lf%lf%lf%lf", &r, &p.x, &p.y, &q.x, &q.y);
    if (p == q) {
      printf("%.10f\n", 2 * (r - Length(p)));
      continue;
    }
    Circle O(Point(0, 0), r);
    Point pp = Inversion_P2P(O.c, r, p);
    Point qq = Inversion_P2P(O.c, r, q);
    vector<Point> ps = CircleXLine(O, {pp, qq - pp});
    db ans = 1e9;
    if (ps.size()) {
      ans = Length(ps[0] - p) + Length(ps[0] - q);
    } else {
      Line l = PerpendicularBisector(pp, qq);
      ps = CircleXLine(O, l);
      for (auto& u : ps) ans = min(ans, Length(u - p) + Length(u - q));
    }
    printf("%.8f\n", ans);
  }
}