#include <bits/stdc++.h>
using namespace std;
const int mod = 998244353;
const int maxn = 1e6 + 6;
int a[maxn], b[maxn];
int inv2 = (mod + 1) / 2;

template <class T>
void fwt(int a[], int m, T f) {
  for (int i = 1; i < m; i <<= 1)
    for (int p = i << 1, j = 0; j < m; j += p)
      for (int k = 0; k < i; k++) f(a[j + k], a[i + j + k]);
}

inline void AND(int &a, int &b) { (a += b) %= mod; }
inline void OR(int &a, int &b) { (b += a) %= mod; }
inline void XOR(int &a, int &b) {
  int l = a, r = b;
  a = (l + r) % mod, b = (l - r + mod) % mod;
}
inline void rAND(int &a, int &b) { a = (a - b + mod) % mod; }
inline void rOR(int &a, int &b) { b = (b - a + mod) % mod; }
inline void rXOR(int &a, int &b) {
  int l = a, r = b;
  a = 1LL * (l + r) % mod * inv2 % mod;
  b = 1LL * (l - r + mod) % mod * inv2 % mod;
}

int c[maxn], d[maxn];
int n, N;

void solve(int a[], int b[], int op) {
  for (int i = 0; i < N; i++) c[i] = a[i], d[i] = b[i];
  if (op == 0) {
    fwt(c, N, OR);
    fwt(d, N, OR);
    for (int i = 0; i < N; i++) c[i] = 1LL * c[i] * d[i] % mod;
    fwt(c, N, rOR);
  } else if (op == 1) {
    fwt(c, N, AND);
    fwt(d, N, AND);
    for (int i = 0; i < N; i++) c[i] = 1LL * c[i] * d[i] % mod;
    fwt(c, N, rAND);
  } else {
    fwt(c, N, XOR);
    fwt(d, N, XOR);
    for (int i = 0; i < N; i++) c[i] = 1LL * c[i] * d[i] % mod;
    fwt(c, N, rXOR);
  }
  for (int i = 0; i < N; i++) printf("%d ", c[i]);
  puts("");
}
int main() {
  scanf("%d", &n);
  N = 1 << n;
  for (int i = 0; i < N; i++) scanf("%d", a + i);
  for (int i = 0; i < N; i++) scanf("%d", b + i);
  solve(a, b, 0);
  solve(a, b, 1);
  solve(a, b, 2);
}