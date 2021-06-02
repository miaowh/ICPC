#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 5e4 + 5;
const int S = 300;
struct Q {
  int l, r, id;
  bool operator<(const Q& rhs) const {
    if (l / S == rhs.l / S) return r < rhs.r;
    return l < rhs.l;
  }
} q[maxn];
int a[maxn], col[maxn];
ll ans[maxn][2];

ll num, denom, sum;
void move(int p, int sign) {
  if (sign == 1) {
    denom += sum;
    num += col[a[p]];
    sum++;
    col[a[p]]++;
  } else {
    sum--;
    col[a[p]]--;
    denom -= sum;
    num -= col[a[p]];
  }
}
int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) scanf("%d", a + i);
  for (int i = 0, l, r; i < m; i++) {
    scanf("%d%d", &l, &r);
    q[i] = {l, r, i};
  }
  sort(q, q + m);
  denom = num = sum = 0;
  int l = 1, r = 1;
  for (int i = 0; i < m; i++) {
    while (l < q[i].l) move(l++, -1);
    while (l > q[i].l) move(--l, 1);
    while (r <= q[i].r) move(r++, 1);
    while (r > q[i].r + 1) move(--r, -1);
    ll d = __gcd(num, denom);
    ans[q[i].id][0] = num / d, ans[q[i].id][1] = denom / d;
  }
  for (int i = 0; i < m; i++) printf("%lld/%lld\n", ans[i][0], ans[i][1]);
}