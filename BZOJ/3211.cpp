// ybmj
#include <bits/stdc++.h>
using namespace std;
#define lson (rt << 1)
#define rson (rt << 1 | 1)
#define lson_len (len - (len >> 1))
#define rson_len (len >> 1)
#define pb(x) push_back(x)
#define clr(a, x) memset(a, x, sizeof(a))
#define mp(x, y) make_pair(x, y)
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
#define my_unique(a) a.resize(distance(a.begin(), unique(a.begin(), a.end())))
#define my_sort_unique(c) (sort(c.begin(), c.end())), my_unique(c)
const double PI = acos(-1.0);
const int INF = 0x3f3f3f3f;
const int NINF = 0xc0c0c0c0;
const int maxn = 1e5 + 5;

struct Node {
    ll sum;
    int Max;
};
Node seg[maxn << 2];
int a[maxn];

inline void pushup(int rt) {
    seg[rt].Max = max(seg[lson].Max, seg[rson].Max);
    seg[rt].sum = seg[lson].sum + seg[rson].sum;
}
void build(int rt, int l, int r) {
    if (l == r) {
        seg[rt].Max = a[l];
        seg[rt].sum = a[l];
        return;
    }
    int mid = l + r >> 1;
    build(lson, l, mid);
    build(rson, mid + 1, r);
    pushup(rt);
}
void update(int rt, int l, int r, int L, int R) {
    if (seg[rt].Max <= 1) return;
    if (l == r) {
        seg[rt].Max = sqrt(seg[rt].Max);
        seg[rt].sum = sqrt(seg[rt].sum);
        return;
    }
    int mid = l + r >> 1;
    if (mid >= L) update(lson, l, mid, L, R);
    if (mid + 1 <= R) update(rson, mid + 1, r, L, R);
    pushup(rt);
}
ll query(int rt, int l, int r, int L, int R) {
    if (L <= l && R >= r) {
        return seg[rt].sum;
    }
    ll ret = 0;
    int mid = l + r >> 1;
    if (mid >= L) ret += query(lson, l, mid, L, R);
    if (mid + 1 <= R) ret += query(rson, mid + 1, r, L, R);
    return ret;
}
int main() {
    //  /*
#ifndef ONLINE_JUDGE
    freopen("1.in", "r", stdin);
    freopen("1.out", "w", stdout);
#endif
    //  */
    std::ios::sync_with_stdio(false);
    int n, m;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    scanf("%d", &m);
    build(1, 1, n);
    while (m--) {
        int x, l, r;
        scanf("%d%d%d", &x, &l, &r);
        if (x == 1) {
            printf("%lld\n", query(1, 1, n, l, r));
        } else {
            update(1, 1, n, l, r);
        }
    }
}