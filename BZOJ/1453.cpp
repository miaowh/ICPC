
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
const int maxn = 205;
int n, grid[maxn * maxn], par[maxn << 2];

inline int find(int x) { return x == par[x] ? x : par[x] = find(par[x]); }
inline bool merge(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return false;
    par[x] = y;
    return true;
}
struct Seg {
    int up, down, pup[maxn], pdown[maxn], cnt[2];

    void assign(int p) {
        cnt[0] = cnt[1] = 0;
        for (int i = 1; i <= n; i++) par[i] = i;
        for (int i = 1, id; i <= n; i++) {
            id = (p - 1) * n + i;
            if (i > 1 && grid[id - 1] == grid[id])
                merge(i - 1, i);
            else
                cnt[grid[id]]++;
        }
        for (int i = 1; i <= n; i++) pup[i] = pdown[i] = find(i);
    }
};
Seg seg[maxn << 2];

inline void pushup(int rt) {
    for (int i = 0; i < 2; i++)
        seg[rt].cnt[i] = seg[lson].cnt[i] + seg[rson].cnt[i];
    for (int i = 1; i <= 4 * n; i++) par[i] = i;
    for (int i = 1; i <= n; i++) {
        int up = (seg[lson].down - 1) * n + i;
        int dn = (seg[rson].up - 1) * n + i;
        if (grid[up] == grid[dn] &&
            merge(seg[lson].pdown[i], seg[rson].pup[i] + 2 * n))
            seg[rt].cnt[grid[up]]--;
    }
    map<int, int> id;
    int tot = 1;
    for (int i = 1, x; i <= n; i++) {
        x = find(seg[lson].pup[i]);
        seg[rt].pup[i] = (id[x] == 0) ? id[x] = tot++ : id[x];
        x = find(seg[rson].pdown[i] + 2 * n);
        seg[rt].pdown[i] = (id[x] == 0) ? id[x] = tot++ : id[x];
    }
}
void build(int l, int r, int rt) {
    seg[rt].up = l;
    seg[rt].down = r;
    if (l == r) {
        seg[rt].assign(l);
        return;
    }
    int m = l + r >> 1;
    build(l, m, lson);
    build(m + 1, r, rson);
    pushup(rt);
}
void update(int l, int r, int rt, int x) {
    if (l == r) {
        seg[rt].assign(l);
        return;
    }
    int m = l + r >> 1;
    if (x <= m)
        update(l, m, lson, x);
    else
        update(m + 1, r, rson, x);
    pushup(rt);
}
int main() {
//  /*
#ifndef ONLINE_JUDGE
    freopen("1.in", "r", stdin);
    freopen("1.out", "w", stdout);
#endif
    //  */
    std::ios::sync_with_stdio(false);
    scanf("%d", &n);
    for (int i = 1, id; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            id = (i - 1) * n + j;
            scanf("%d", grid + id);
        }
    }
    build(1, n, 1);
    int m, x, y;
    scanf("%d", &m);
    while (m--) {
        scanf("%d%d", &x, &y);
        grid[(x - 1) * n + y] ^= 1;
        update(1, n, 1, x);
        printf("%d %d\n", seg[1].cnt[1], seg[1].cnt[0]);
    }
}