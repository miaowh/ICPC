#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e4 + 4;
const int S = 150;
struct Query {
  int l, r, t, c;
  bool operator<(const Query &rhs) const {
    if (l / S == rhs.l / S) {
      if (r / S == rhs.r / S)
        return t < rhs.t;
      else
        r < rhs.r;
    }
    return l < rhs.l;
  }
} q[maxn];
int a[maxn];
int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) scanf("%d", a + i);
  char op[2];
  for (int i = 0, x, y; i < m; i++) {
    scanf("%s%d%d", op, x, y);
    q[i] = {x, y, i, op[0] == 'Q' ? 0 : 1};
  }
  sort(q, q + m);
  int l = 0, r = 0, t = 0;
  for (int i = 0; i < m; i++) {
  }
}
