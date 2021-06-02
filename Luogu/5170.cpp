#include <bits/stdc++.h>
using namespace std;
using ll = long long;

namespace likeGcd {
using ll = long long;
const ll mod = 998244353;
const ll inv2 = 499122177;
const ll inv6 = 166374059;
ll n, a, b, c;

struct node {
  ll f, g, h;
};

inline ll S1(ll n) { return n * (n + 1) % mod * inv2 % mod; }

inline ll S2(ll n) {
  return n * (n + 1) % mod * (2 * n + 1) % mod * inv6 % mod;
}

inline node solve(ll a, ll b, ll c, ll n) {
  ll t1 = a / c, t2 = b / c, s1 = S1(n), s2 = S2(n), m = (a * n + b) / c;
  node ans, now;
  ans.f = ans.g = ans.h = 0;
  if (!n) {
    ans.f = t2;
    ans.g = t2 * t2 % mod;
    return ans;
  }
  if (!a) {
    ans.f = (n + 1) * t2 % mod;
    ans.g = (n + 1) * t2 % mod * t2 % mod;
    ans.h = t2 * s1 % mod;
    return ans;
  }
  if (a >= c || b >= c) {
    now = solve(a % c, b % c, c, n);
    ans.f = (now.f + t1 * s1 + (n + 1) * t2) % mod;
    ans.g = (now.g + 2 * t1 * now.h + 2 * t2 * now.f + t1 * t1 % mod * s2 +
             2 * t1 * t2 % mod * s1 + (n + 1) * t2 % mod * t2) %
            mod;
    ans.h = (now.h + t1 * s2 + t2 * s1) % mod;
    return ans;
  }
  now = solve(c, c - b - 1, a, m - 1);
  ans.f = (m * n - now.f) % mod;
  ans.f = (ans.f + mod) % mod;
  ans.g = (m * m % mod * n - 2 * now.h - now.f);
  ans.g = (ans.g + mod) % mod;
  ans.h = (m * s1 - now.g * inv2 - now.f * inv2) % mod;
  ans.h = (ans.h + mod) % mod;
  return ans;
}

};  // namespace likeGcd

int main() {
  ll T;
  scanf("%lld", &T);
  while (T--) {
    scanf("%lld%lld%lld%lld", &n, &a, &b, &c);
    node ans = solve(a, b, c, n);
    printf("%lld %lld %lld\n", ans.f, ans.g, ans.h);
  }
  return 0;
}