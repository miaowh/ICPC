#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 6;
const int mod = 998244353;
int f[maxn];
int a[maxn];
int bit[maxn];
int n;
inline int lowbit(int x) { return x & (-x); }
void add(int x, int w) {
  for (int i = x; i <= n; i += lowbit(i)) bit[i] += w;
}
int query(int l, int r) {
  if (l > r) return 0;
  int ret = 0;
  for (int i = r; i > 0; i -= lowbit(i)) ret += bit[i];
  for (int i = l - 1; i > 0; i -= lowbit(i)) ret -= bit[i];
  return ret;
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) scanf("%d", a + i), add(i, 1);
  f[0] = 1;
  for (int i = 1; i <= n; i++) f[i] = 1LL * f[i - 1] * i % mod;

  set<int> num;
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    int cnt = query(1, a[i] - 1);
    ans = (ans + 1LL * cnt * f[n - i] % mod) % mod;
    add(a[i], -1);
  }
  printf("%d\n", ans + 1);
}