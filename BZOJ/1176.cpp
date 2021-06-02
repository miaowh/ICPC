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
const int maxn = 2e5 + 5;
const int maxm = 2e6 + 5;
struct P {
    int op, x, y, val, id, qid;
    bool operator<(const P& A) const { return x < A.x; }
};
P a[maxn << 2], tmp[maxn << 2];
int ans[maxn];
int BIT[maxm];
int n, s, w;
inline int lowb(int x) { return x & (-x); }
inline int query(int l, int r) {
    int ret = 0;
    for (int i = l - 1; i > 0; i -= lowb(i)) ret -= BIT[i];
    for (int i = r; i > 0; i -= lowb(i)) ret += BIT[i];
    return ret;
}
inline void update(int x, int y) {
    for (int i = x; i <= w; i += lowb(i)) BIT[i] += y;
}

void solve(int l, int r) {
    if (l == r) return;
    int mid = l + r >> 1;
    int l1 = l, l2 = mid + 1;
    for (int i = l; i <= r; i++) {
        if (a[i].id <= mid)
            tmp[l1++] = a[i];
        else
            tmp[l2++] = a[i];
    }
    for (int i = l; i <= r; i++) a[i] = tmp[i];
    solve(l, mid);

    l1 = l;
    for (int i = mid + 1; i <= r; i++) {
        while (l1 <= mid && a[l1].x <= a[i].x) {
            if (a[l1].op == 1) update(a[l1].y, a[l1].val);
            l1++;
        }
        if (a[i].op == 1) continue;
        ans[a[i].qid] += a[i].val * query(1, a[i].y);
    }
    for (int i = l; i < l1; i++) {
        if (a[i].op == 1) update(a[i].y, -a[i].val);
    }

    solve(mid + 1, r);

    l1 = l, l2 = mid + 1;
    int l3 = l;
    while (l1 <= mid && l2 <= r) {
        if (a[l1].x > a[l2].x)
            tmp[l3++] = a[l2++];
        else
            tmp[l3++] = a[l1++];
    }
    while (l1 <= mid) tmp[l3++] = a[l1++];
    while (l2 <= r) tmp[l3++] = a[l2++];
    for (int i = l; i <= r; i++) a[i] = tmp[i];
}
int main() {
    //	/*
#ifndef ONLINE_JUDGE
    freopen("1.in", "r", stdin);
    freopen("1.out", "w", stdout);
#endif
    //	*/
    std::ios::sync_with_stdio(false);
    scanf("%d%d", &s, &w);
    clr(ans, -1);
    int op, x1, x2, y1, y2, val;
    n = 0;
    int cnt = 0;
    while (true) {
        scanf("%d", &op);
        if (op == 3) break;
        if (op == 1) {
            scanf("%d%d%d", &x1, &y1, &val);
            a[++n] = {op, x1, y1, val, n, -1};
        } else {
            scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
            ++cnt;
            ans[cnt] = 0;
            a[++n] = {op, x2, y2, 1, n, cnt};
            a[++n] = {op, x1 - 1, y2, -1, n, cnt};
            a[++n] = {op, x2, y1 - 1, -1, n, cnt};
            a[++n] = {op, x1 - 1, y1 - 1, 1, n, cnt};
        }
    }
    sort(a + 1, a + n + 1);
    solve(1, n);
    for (int i = 1; i <= cnt; i++) {
        if (ans[i] == -1)
            continue;
        else
            printf("%d\n", ans[i]);
    }
}