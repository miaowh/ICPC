#include <bits/stdc++.h>
using namespace std;
const int maxn = 3e5 + 5;
using ll = long long;
int a[maxn], ans[maxn];
int le[maxn], ri[maxn], x[maxn];
vector<int> G[maxn];
int n, m, q;

__int128 diff[maxn];
inline int lowb(int x) { return x & (-x); }
inline __int128 query(int x) {
  __int128 ret = 0;
  for (int i = x; i > 0; i -= lowb(i)) ret += diff[i];
  return ret;
}
inline void add(int l, int r, int val) {
  for (int i = l; i <= m; i += lowb(i)) diff[i] += val;
  for (int i = r + 1; i <= m; i += lowb(i)) diff[i] -= val;
}

void update(int l, int r, int sign) {
  for (int i = l; i <= r; i++) {
    if (ri[i] >= le[i])
      add(le[i], ri[i], sign * x[i]);
    else {
      add(le[i], m, sign * x[i]);
      add(1, ri[i], sign * x[i]);
    }
  }
}

void solve(int l, int r, vector<int> c) {
  if (c.empty()) return;
  if (l == r) {
    for (auto &u : c) ans[u] = l;
    return;
  }
  int m = l + r >> 1;
  update(l, m, 1);
  vector<int> left, right;
  for (auto &u : c) {
    __int128 sum = 0;
    for (auto &v : G[u]) sum += query(v);
    if (sum >= a[u]) {
      left.push_back(u);
    } else {
      a[u] -= sum;
      right.push_back(u);
    }
  }
  update(l, m, -1);
  solve(l, m, left);
  solve(m + 1, r, right);
}
int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1, c; i <= m; i++) scanf("%d", &c), G[c].push_back(i);
  for (int i = 1; i <= n; i++) scanf("%d", a + i);
  scanf("%d", &q);
  for (int i = 1; i <= q; i++) scanf("%d%d%d", le + i, ri + i, x + i);
  vector<int> c(n);
  for (int i = 1; i <= n; i++) c[i - 1] = i;
  solve(1, q + 1, c);
  for (int i = 1; i <= n; i++)
    if (ans[i] == q + 1)
      puts("NIE");
    else
      printf("%d\n", ans[i]);
}