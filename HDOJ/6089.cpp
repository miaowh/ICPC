#include <bits/stdc++.h>
using namespace std;
#define lson (rt << 1)
#define rson (rt << 1 | 1)
typedef long long ll;
const int maxn = 1e5 + 5;
struct P {
  int x, y, id;
};
P unsafe[maxn], safe[maxn];
set<int> S[maxn], SS;
map<int, int> M[maxn];
int n, m, K, q;

struct Node {
  int mi, ma;
  int lmi, lma, rmi, rma;
} seg[maxn << 2];

ll golmi(int l, int r, int rt, int pre) {
  if (pre <= seg[rt].mi) return 1LL * pre * (r - l + 1);
  if (l == r) return seg[rt].mi;
  int mid = l + r >> 1;
  if (pre <= seg[rson].mi)
    return 1LL * pre * (r - mid) + golmi(l, mid, lson, pre);
  else
    return golmi(mid + 1, r, rson, pre) + seg[rt].lmi;
}
void pushup(int l, int r, int rt) {
  Node &ls = seg[lson], &rs = seg[rson], &o = seg[rt];
  int mid = l + r >> 1;
  o.mi = min(ls.mi, rs.mi);
  o.ma = max(ls.ma, rs.ma);
  o.lmi = golmi(l, mid, lson, rs.mi);
}
void build(int l, int r, int rt) {
  if (l == r) {
    auto it = S[l].begin();
    it++;
    seg[rt].mi = *k;
    seg[rt].ma = 0;
    return;
  }
  int mid = l + r >> 1;
  build(l, m, lson);
  build(m + 1, r, rson);
  // pushup()
}
int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d%d%d", &n, &m, &K, &q);
    for (int i = 1; i <= m; i++) {
      S[i].clear();
      S[i].insert(0);
      S[i].insert(1 + n);
      M[i].clear();
    }
    for (int i = 1; i <= K; i++) {
      scanf("%d%d", &unsafe[i].x, &unsafe[i].y);
      S[unsafe[i].y].insert(unsafe[i].x);
      M[unsafe[i].y][unsafe[i].x] = 1;
    }
    for (int i = 1; i <= q; i++) {
      scanf("%d%d", &safe[i].x, &safe[i].y);
      safe[i].id = i;
    }
    sort(safe + 1, safe + 1 + n,
         [&](const P &a, const P &b) { return a.x < b.x; });
    build(1, m, 1);
  }
}