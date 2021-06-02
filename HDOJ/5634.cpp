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
const int INF = 0x3f3f3f3f;
const int NINF = 0xc0c0c0c0;
const double PI = acos(-1.0);
const int maxn = 3e5 + 5;
const int N = 1e7 + 7;
bool vis[N];
int tot, phi[N], prime[N];
void Calphi() {
    tot = 0;
    phi[1] = 1;
    for (int i = 2; i < N; i++) {
        if (!vis[i]) prime[tot++] = i, phi[i] = i - 1;
        for (int j = 0; j < tot; j++) {
            if (i * prime[j] > N) break;
            vis[i * prime[j]] = 1;
            if (i % prime[j] == 0) {
                phi[i * prime[j]] = phi[i] * prime[j];
                break;
            } else
                phi[i * prime[j]] = phi[i] * (prime[j] - 1);
        }
    }
}
struct Node {
    int Max, Min, tag_set, tag_phi;
    ll sum;
    void assign(int x, int len) {
        Max = Min = x;
        sum = 1LL * len * x;
    }
} seg[maxn << 2];

inline void pushup(int rt) {
    seg[rt].Max = max(seg[lson].Max, seg[rson].Max);
    seg[rt].Min = min(seg[lson].Min, seg[rson].Min);
    seg[rt].sum = seg[lson].sum + seg[rson].sum;
}
inline void pushdown(int rt, int len) {
    int x = seg[rt].tag_set;
    if (x) {
        seg[lson].assign(x, lson_len);
        seg[rson].assign(x, rson_len);
        seg[lson].tag_set = seg[rson].tag_set = x;
        seg[lson].tag_phi = seg[rson].tag_phi = 0;
        seg[rt].tag_set = 0;
    }
    while (seg[rt].tag_phi--) {
        x = phi[seg[lson].Max];
        seg[lson].assign(x, lson_len);
        x = phi[seg[rson].Max];
        seg[rson].assign(x, rson_len);
        seg[lson].tag_phi++;
        seg[rson].tag_phi++;
    }
    seg[rt].tag_phi = 0;
}
void build(int l, int r, int rt) {
    seg[rt].tag_set = seg[rt].tag_phi = 0;
    if (l == r) {
        int x;
        scanf("%d", &x);
        seg[rt].assign(x, 1);
        return;
    }
    int m = l + r >> 1;
    build(l, m, lson);
    build(m + 1, r, rson);
    pushup(rt);
}
void update(int l, int r, int rt, int L, int R, int op, int x = -1) {
    int m = l + r >> 1;
    if (L <= l && r <= R) {
        if (op == 1) {
            if (seg[rt].Max == 1) return;
            if (seg[rt].Max == seg[rt].Min) {
                seg[rt].assign(phi[seg[rt].Max], r - l + 1);
                seg[rt].tag_phi++;
                return;
            }
            update(l, m, lson, L, R, op);
            update(m + 1, r, rson, L, R, op);
            pushup(rt);
        } else {
            seg[rt].assign(x, r - l + 1);
            seg[rt].tag_set = x;
            seg[rt].tag_phi = 0;
        }
        return;
    }
    pushdown(rt, r - l + 1);
    if (L <= m) update(l, m, lson, L, R, op, x);
    if (m + 1 <= R) update(m + 1, r, rson, L, R, op, x);
    pushup(rt);
}
ll query(int l, int r, int rt, int L, int R) {
    if (L <= l && r <= R) return seg[rt].sum;
    pushdown(rt, r - l + 1);
    ll ret = 0;
    int m = l + r >> 1;
    if (L <= m) ret += query(l, m, lson, L, R);
    if (m + 1 <= R) ret += query(m + 1, r, rson, L, R);
    return ret;
}
int main() {
    /*
#ifndef ONLINE_JUDGE
freopen("1.in", "r", stdin);
freopen("1.out", "w", stdout);
#endif
    */
    std::ios::sync_with_stdio(false);
    Calphi();
    int T;
    scanf("%d", &T);
    while (T--) {
        int n, m;
        scanf("%d%d", &n, &m);
        build(1, n, 1);
        int op, l, r, x;
        while (m--) {
            scanf("%d%d%d", &op, &l, &r);
            if (op == 1)
                update(1, n, 1, l, r, op);
            else if (op == 2) {
                scanf("%d", &x);
                update(1, n, 1, l, r, op, x);
            } else
                printf("%lld\n", query(1, n, 1, l, r));
        }
    }
}