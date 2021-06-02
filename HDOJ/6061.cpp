#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 119 << 23 | 1;
const int G = 3;
int wn[20];
int Pow(int a, int b, int p) {
  int ret = 1;
  while (b) {
    if (b & 1) ret = 1LL * ret * a % p;
    a = 1LL * a * a % p;
    b >>= 1;
  }
  return ret;
}
void getwn() {  //  千万不要忘记
  for (int i = 0; i < 20; i++) wn[i] = Pow(G, (mod - 1) / (1 << i), mod);
}
void change(int y[], int len) {
  for (int i = 1, j = len / 2; i < len - 1; i++) {
    if (i < j) swap(y[i], y[j]);
    int k = len / 2;
    while (j >= k) j -= k, k /= 2;
    if (j < k) j += k;
  }
}
void ntt(int y[], int len, int on) {
  change(y, len);
  for (int h = 2, id = 1; h <= len; h <<= 1, id++) {
    for (int j = 0; j < len; j += h) {
      int w = 1;
      for (int k = j; k < j + h / 2; k++) {
        int u = y[k] % mod;
        int t = 1LL * w * (y[k + h / 2] % mod) % mod;
        y[k] = (u + t) % mod, y[k + h / 2] = ((u - t) % mod + mod) % mod;
        w = 1LL * w * wn[id] % mod;
      }
    }
  }
  if (on == -1) {
    //  原本的除法要用逆元
    int inv = Pow(len, mod - 2, mod);
    for (int i = 1; i < len / 2; i++) swap(y[i], y[len - i]);
    for (int i = 0; i < len; i++) y[i] = 1LL * y[i] * inv % mod;
  }
}
const int maxn = 4e5 + 5;
int c[maxn], A[maxn], B[maxn];
int fac[maxn], inv[maxn], ap[maxn];
void init() {
  fac[0] = 1;
  for (int i = 1; i < maxn; i++) fac[i] = 1LL * fac[i - 1] * i % mod;
  inv[maxn - 1] = Pow(fac[maxn - 1], mod - 2, mod);
  for (int i = maxn - 2; i >= 0; i--) inv[i] = 1LL * inv[i + 1] * (i + 1) % mod;
}
int main() {
  getwn();
  init();
  int n, m;
  while (~scanf("%d", &n)) {
    for (int i = 0; i <= n; i++) scanf("%d", c + i);
    scanf("%d", &m);
    int a = 0;
    for (int i = 1, x; i <= m; i++) scanf("%d", &x), a = (ll(a) + x) % mod;
    a = (-a + mod) % mod;
    int len = 1;
    while (len <= (n << 1)) len <<= 1;
    ap[0] = 1;
    for (int i = 1; i <= n; i++) ap[i] = 1LL * ap[i - 1] * a % mod;
    for (int i = 0; i <= n; i++) {
      A[i] = 1LL * c[n - i] * fac[n - i] % mod;
      B[i] = 1LL * ap[i] * inv[i] % mod;
    }
    for (int i = n + 1; i <= len; i++) A[i] = B[i] = 0;
    ntt(A, len, 1);
    ntt(B, len, 1);
    for (int i = 0; i < len; i++) A[i] = 1LL * A[i] * B[i] % mod;
    ntt(A, len, -1);
    for (int i = 0; i <= n; i++) B[n - i] = 1LL * A[i] * inv[n - i] % mod;
    for (int i = 0; i <= n; i++) printf("%d%c", B[i], (i == n ? '\n' : ' '));
  }
}