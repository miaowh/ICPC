#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int mod = 1e9 + 7;
const int maxn = 2e5 + 5;
int a[maxn];
ll dp[maxn], f[maxn];

ll Pow(ll a, ll b) {
  ll ret = 1;
  while (b) {
    if (b & 1) ret = ret * a % mod;
    a = a * a % mod;
    b >>= 1;
  }
  return ret;
}
inline ll inv(ll x) { return Pow(x, mod - 2); }
ll C(ll n, ll m) {
  if (n < m) return 0;
  return f[n] * inv(f[m] * f[n - m] % mod) % mod;
}
int main() {
  f[0] = 1;
  for (int i = 1; i < maxn; i++) f[i] = f[i - 1] * i % mod;

  int T;
  scanf("%d", &T);
  while (T--) {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < 2 * n; i++) scanf("%d", a + i);
    int p = 0;
    dp[0] = 1;
    for (int i = 1; i <= 2 * n; i++) {
      int k = 0, t;
      while (p < 2 * n && a[p] <= i) {
        k++;
        p++;
      }
      t = p - k;
      if (t & 1) {
        if (p & 1) {
          dp[i] = dp[i - 1] * (C(k, k / 2) + C(k, k / 2 + 1)) % mod;
        } else {
          dp[i] = dp[i - 1] * C(k, k / 2) % mod;
        }
      } else {
        if (p & 1) {
          dp[i] = dp[i - 1] * C(k, k / 2) % mod * 2LL % mod;
        } else {
          dp[i] = dp[i - 1] * C(k, k / 2) % mod;
        }
      }
    }
    printf("%lld\n", dp[2 * n]);
  }
}