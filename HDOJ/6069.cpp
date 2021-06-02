#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int maxn = 1e6 + 6;
bool is_prime_small[maxn], is_prime[maxn];
ll prime[maxn], sum[maxn], val[maxn];
ll l, r, k;

///[a,b)
int segment_sieve(ll a, ll b) {
  int tot = 0;
  for (ll i = 0; i * i < b; i++) is_prime_small[i] = true;
  for (ll i = 0; i < b - a; i++) is_prime[i] = true;
  for (ll i = 2; i * i < b; i++) {
    if (is_prime_small[i]) {
      for (ll j = 2 * i; j * j < b; j += i) is_prime_small[j] = false;
      for (ll j = max(2LL, (a + i - 1) / i) * i; j < b; j += i) {
        ll tmp = val[j - a];
        ll cnt = 0;
        while (tmp % i == 0) {
          tmp /= i;
          cnt++;
        }
        val[j - a] = tmp;
        sum[j - a] = sum[j - a] * (1 + k * cnt % mod) % mod;
        is_prime[j - a] = false;
      }
    }
  }
  for (ll i = 0; i < b - a; i++)
    if (is_prime[i]) prime[tot++] = i + a;
  return tot;
}
int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    scanf("%lld%lld%lld", &l, &r, &k);
    for (int i = 0; i <= r - l; i++) sum[i] = 1, val[i] = i + l;
    int tot = segment_sieve(l, r + 1);
    ll ans = 0;
    for (ll i = l; i <= r; i++) {
      if (i == 1) {
        ans = (ans + 1) % mod;
        continue;
      }
      if (is_prime[i - l]) {
        ans = (ans + 1 + k) % mod;
      } else {
        if (val[i - l] != 1) sum[i - l] = sum[i - l] * (1 + k) % mod;
        ans = (ans + sum[i - l]) % mod;
      }
    }
    printf("%lld\n", ans);
  }
}