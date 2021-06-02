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
const int maxn = 5e4 + 5;
ll pre[maxn], a[maxn], c[maxn], dp[maxn];

inline double slope(int i, int k) {
    return 1.0 * ((dp[i] + a[i] * a[i]) - (dp[k] + a[k] * a[k])) /
           (a[i] - a[k]);
}
int main() {
    //	/*
#ifndef ONLINE_JUDGE
    freopen("1.in", "r", stdin);
    freopen("1.out", "w", stdout);
#endif
    //	*/
    std::ios::sync_with_stdio(false);
    int n, L;
    scanf("%d%d", &n, &L);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &c[i]), pre[i] = pre[i - 1] + c[i], a[i] = pre[i] + i;
    int b = 1 + L;
    int l = 1, r = 1;
    vector<int> dq(n + 2);
    dq[1] = 0;
    for (int i = 1; i <= n; i++) {
        while (l < r && slope(dq[l], dq[l + 1]) < 2 * a[i] - 2 * b) l++;
        int k = dq[l];
        dp[i] = dp[k] + (a[i] - a[k] - b) * (a[i] - a[k] - b);
        while (l < r && slope(dq[r], i) < slope(dq[r - 1], dq[r])) r--;
        dq[++r] = i;
    }
    printf("%lld\n", dp[n]);
}