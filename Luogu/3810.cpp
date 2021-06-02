#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 5;
using ll = long long;
struct Node {
  int a, b, c, id, num, ans;
  bool operator==(const Node &rhs) const {
    return (a == rhs.a && b == rhs.b && c == rhs.c);
  }
} a[maxn];
int ans[maxn];
int n, k;

int sum[maxn];

inline void add(int p, int x) {
  for (int i = p; i <= k; i += i & -i) sum[i] += x;
}
inline int query(int l, int r) {
  int ret = 0;
  for (int i = r; i > 0; i -= i & -i) ret += sum[i];
  for (int i = l - 1; i > 0; i -= i & -i) ret -= sum[i];
  return ret;
}

void solve(int l, int r) {
  if (r - l <= 1) return;
  int m = l + r >> 1;
  solve(l, m);
  solve(m, r);
  int p = l;
  for (int i = m; i < r; i++) {
    while (p < m && a[p].b <= a[i].b) add(a[p].c, a[p].num), p++;
    a[i].ans += query(1, a[i].c);
  }
  for (int i = l; i < p; i++) add(a[i].c, -a[i].num);
  sort(a + l, a + r, [&](const Node &A, const Node &B) {
    if (A.b == B.b) return A.c < B.c;
    return A.b < B.b;
  });
}
int main() {
  scanf("%d%d", &n, &k);
  for (int i = 0; i < n; i++)
    scanf("%d%d%d", &a[i].a, &a[i].b, &a[i].c), a[i].id = i, a[i].num = 1,
                                                a[i].ans = 0;
  sort(a, a + n, [&](const Node &A, const Node &B) {
    if (A.a == B.a && A.b == B.b) return A.c < B.c;
    if (A.a == B.a) return A.b < B.b;
    return A.a < B.a;
  });
  int m = 0;
  for (int i = 1; i < n; i++) {
    if (a[i] == a[m])
      a[m].num++;
    else
      a[++m] = a[i];
  }
  solve(0, m + 1);
  for (int i = 0; i <= m; i++) ans[a[i].ans + a[i].num - 1] += a[i].num;
  for (int i = 0; i < n; i++) printf("%d\n", ans[i]);
}