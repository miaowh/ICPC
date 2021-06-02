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
const int maxn = 1e5 + 5;
const int mod = 1e9 + 7;
ll Hash[maxn << 2][2], a[maxn];
ll Pow[maxn];

inline void pushup(int rt, int len) {
    Hash[rt][0] = (Pow[rson_len] * Hash[lson][0] % mod + Hash[rson][0]) % mod;
    Hash[rt][1] = (Pow[lson_len] * Hash[rson][1] % mod + Hash[lson][1]) % mod;
}
void update(int l, int r, int rt, int p) {
    if (l == r) {
        Hash[rt][0] = 1;
        Hash[rt][1] = 1;
        return;
    }
    int m = l + r >> 1;
    if (p <= m)
        update(l, m, lson, p);
    else
        update(m + 1, r, rson, p);
    pushup(rt, r - l + 1);
}
ll query(int l, int r, int rt, int L, int R, int x) {
    if (L <= l && r <= R) return Hash[rt][x];
    int m = l + r >> 1;
    if (m >= R)
        return query(l, m, lson, L, R, x);
    else if (m + 1 <= L)
        return query(m + 1, r, rson, L, R, x);
    else {
        ll t1 = query(l, m, lson, L, R, x);
        ll t2 = query(m + 1, r, rson, L, R, x);
        if (!x) return (t1 * Pow[min(R - m, r - m)] % mod + t2) % mod;  // !
        return (t2 * Pow[min(m + 1 - L, m + 1 - l)] % mod + t1) % mod;
    }
}
/*
ll query(int l, int r, int rt, int L, int R, int x) {
    ll ans = 0;
    if (l == L && r == R) return Hash[rt][x];
    int m = l + r >> 1;
    if (R <= m)
        return query(l, m, lson, L, R, x);
    else if (L > m)
        return query(m + 1, r, rson, L, R, x);
    else {
        if (!x)
            return (query(l, m, lson, L, m, x) * Pow[R - m] +
                    query(m + 1, r, rson, m + 1, R, x)) %
                   mod;
        else
            return (query(l, m, lson, L, m, x) +
                    query(m + 1, r, rson, m + 1, R, x) * Pow[m - L + 1]) %
                   mod;
    }
}
*/

int main() {
//	/*
#ifndef ONLINE_JUDGE
    freopen("1.in", "r", stdin);
    freopen("1.out", "w", stdout);
#endif
    //	*/
    std::ios::sync_with_stdio(false);
    int T, n;
    scanf("%d", &T);
    Pow[0] = 1;
    for (int i = 1; i < maxn; i++) Pow[i] = Pow[i - 1] * 3 % mod;
    while (T--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) scanf("%d", a + i);
        clr(Hash, 0);
        bool ok = false;
        for (int i = 1; i <= n; i++) {
            ll len = min(a[i] - 1, n - a[i]);
            if (len) {
                ll t1 = query(1, n, 1, a[i] - len, a[i] - 1, 0);
                ll t2 = query(1, n, 1, a[i] + 1, a[i] + len, 1);
                if (t1 != t2) {
                    ok = true;
                    break;
                }
            }
            update(1, n, 1, a[i]);
        }
        if (ok)
            puts("Y");
        else
            puts("N");
    }
}
