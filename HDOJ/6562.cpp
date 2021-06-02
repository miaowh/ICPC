#include <bits/stdc++.h>
using namespace std;
#define lson (rt << 1)
#define rson (rt << 1 | 1)
#define lson_len (len - (len >> 1))
#define rson_len (len >> 1)
typedef long long ll;
const int mod = 1e9 + 7;
const int maxn = 1e5 + 5;
int tenPow[maxn];
void init() {
  tenPow[0] = 1;
  for (int i = 1; i < maxn; i++) tenPow[i] = tenPow[i - 1] * 10LL % mod;
}
struct Node {
  ll sum, sumLen;
  ll lazyl, lazyr;
  int len;
  Node(ll sum = 0, ll sumLen = 1, ll lazyl = 0, ll lazyr = 0, int len = 0)
      : sum(sum), sumLen(sumLen), lazyl(lazyl), lazyr(lazyr), len(len) {}
} seg[maxn << 2];

void pushup(int rt) {
  Node &o = seg[rt], &ls = seg[lson], &rs = seg[rson];
  o.sum = (ls.sum + rs.sum) % mod;
  o.sumLen = (ls.sumLen + rs.sumLen) % mod;
}
void pushdown(int rt, int len) {
  Node &o = seg[rt], &ls = seg[lson], &rs = seg[rson];
  if (o.len == 0) return;
  ls.sumLen = ls.sumLen * tenPow[o.len] % mod;
  rs.sumLen = rs.sumLen * tenPow[o.len] % mod;

  ls.sum = 1LL * ls.sum * tenPow[o.len] % mod;
  (ls.sum += 1LL * o.lazyr * lson_len % mod) %= mod;
  (ls.sum += 1LL * o.lazyl * ls.sumLen) %= mod;

  rs.sum = 1LL * rs.sum * tenPow[o.len] % mod;
  (rs.sum += 1LL * o.lazyr * rson_len % mod) %= mod;
  (rs.sum += 1LL * o.lazyl * rs.sumLen) %= mod;

  ls.sumLen = ls.sumLen * tenPow[o.len] % mod;
  rs.sumLen = rs.sumLen * tenPow[o.len] % mod;

  ls.lazyl = (o.lazyl * tenPow[ls.len] % mod + ls.lazyl) % mod;
  ls.lazyr = (ls.lazyr * tenPow[o.len] % mod + o.lazyr) % mod;

  rs.lazyl = (o.lazyl * tenPow[rs.len] % mod + rs.lazyl) % mod;
  rs.lazyr = (rs.lazyr * tenPow[o.len] % mod + o.lazyr) % mod;

  ls.len = (ls.len + o.len) % mod;
  rs.len = (rs.len + o.len) % mod;

  o.len = o.lazyl = o.lazyr = 0;
}
void build(int l, int r, int rt) {
  seg[rt].lazyl = seg[rt].lazyr = seg[rt].len = 0;
  if (l == r) {
    seg[rt] = Node();
    return;
  }
  int m = l + r >> 1;
  build(l, m, lson);
  build(m + 1, r, rson);
  pushup(rt);
}

void update(int l, int r, int rt, int L, int R, int d) {
  if (L <= l && R >= r) {
    Node &o = seg[rt];
    o.sum = o.sum * 10LL % mod;
    (o.sum += 1LL * d * (r - l + 1) % mod) %= mod;
    (o.sum += o.sumLen * 10LL % mod * d % mod) %= mod;
    o.sumLen = o.sumLen * 100LL % mod;

    o.lazyl = (1LL * tenPow[o.len] * d % mod + o.lazyl) % mod;
    o.lazyr = (o.lazyr * 10LL % mod + d) % mod;
    o.len++;
    return;
  }
  pushdown(rt, r - l + 1);
  int m = l + r >> 1;
  if (L <= m) update(l, m, lson, L, R, d);
  if (m + 1 <= R) update(m + 1, r, rson, L, R, d);
  pushup(rt);
}
ll query(int l, int r, int rt, int L, int R) {
  if (L <= l && R >= r) return seg[rt].sum;
  pushdown(rt, r - l + 1);
  int m = l + r >> 1;
  ll ret = 0;
  if (L <= m) (ret += query(l, m, lson, L, R)) %= mod;
  if (m + 1 <= R) (ret += query(m + 1, r, rson, L, R)) %= mod;
  return ret;
}

int main() {
  init();
  int T, kase = 1;
  scanf("%d", &T);
  while (T--) {
    int n, m;
    scanf("%d%d", &n, &m);
    char op[20];
    int l, r, d;
    build(1, n, 1);
    printf("Case %d:\n", kase++);
    while (m--) {
      scanf("%s", op);
      if (op[0] == 'w') {
        scanf("%d%d%d", &l, &r, &d);
        update(1, n, 1, l, r, d);
      } else {
        scanf("%d%d", &l, &r);
        printf("%lld\n", query(1, n, 1, l, r));
      }
    }
  }
}