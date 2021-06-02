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
const double eps = 1e-8;
const int maxn = 1e5 + 5;
struct P {
    double a, b, r, k, x, y;
    int id;
    bool operator<(const P &A) const { return k > A.k; }
};
P p[maxn], cpy[maxn];
double dp[maxn];
int q[maxn];
inline double slope(int j, int k) {
    if (fabs(p[j].x - p[k].x) < eps) {
        if (p[k].y - p[j].y > 0)
            return 1e10;
        else
            return -1e9;
    }
    return (p[j].y - p[k].y) / (p[j].x - p[k].x);
}
void solve(int l, int r) {
    if (l == r) {
        dp[l] = max(dp[l - 1], dp[l]);
        p[l].y = dp[l] / (p[l].a * p[l].r + p[l].b);
        p[l].x = p[l].y * p[l].r;
        return;
    }
    int m = l + r >> 1;
    int l1 = l, l2 = m + 1;
    for (int i = l; i <= r; i++) {
        if (p[i].id <= m)
            cpy[l1++] = p[i];
        else
            cpy[l2++] = p[i];
    }
    for (int i = l; i <= r; i++) p[i] = cpy[i];
    solve(l, m);
    int L = l, R = l - 1;
    for (int i = l; i <= m; i++) {
        while (L < R && slope(q[R - 1], q[R]) < slope(q[R], i)) R--;
        q[++R] = i;
    }
    for (int i = m + 1, id; i <= r; i++) {
        while (L < R && slope(q[L], q[L + 1]) > p[i].k) L++;
        id = q[L];
        dp[p[i].id] = max(dp[p[i].id], p[id].x * p[i].a + p[id].y * p[i].b);
    }
    solve(m + 1, r);

    l1 = l, l2 = m + 1;
    int cur = l;
    while (l1 <= m && l2 <= r) {
        if (p[l1].x < p[l2].x + eps)
            cpy[cur++] = p[l1++];
        else
            cpy[cur++] = p[l2++];
    }
    while (l1 <= m) cpy[cur++] = p[l1++];
    while (l2 <= r) cpy[cur++] = p[l2++];
    for (int i = l; i <= r; i++) p[i] = cpy[i];
}
int main() {
    //	/*
#ifndef ONLINE_JUDGE
    freopen("1.in", "r", stdin);
    freopen("1.out", "w", stdout);
#endif
    //	*/
    std::ios::sync_with_stdio(false);
    int n;
    double s;
    scanf("%d%lf", &n, &s);
    for (int i = 1; i <= n; i++) {
        scanf("%lf%lf%lf", &p[i].a, &p[i].b, &p[i].r);
        p[i].id = i;
        p[i].k = -p[i].a / p[i].b;
    }
    sort(p + 1, p + 1 + n);
    dp[0] = s;
    solve(1, n);
    printf("%.3lf\n", dp[n]);
}