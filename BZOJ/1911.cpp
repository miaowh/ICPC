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
const int maxn = 1e6 + 6;
int x[maxn];
ll dp[maxn], pre[maxn];
int n, a, b, c;

inline double slope(int j, int k) {
    double mj = dp[j] + a * pre[j] * pre[j] - b * pre[j];
    double mk = dp[k] + a * pre[k] * pre[k] - b * pre[k];
    return (mj - mk) / (pre[j] - pre[k]);
}
int main() {
    //	/*
#ifndef ONLINE_JUDGE
    freopen("1.in", "r", stdin);
    freopen("1.out", "w", stdout);
#endif
    //	*/
    std::ios::sync_with_stdio(false);
    scanf("%d%d%d%d", &n, &a, &b, &c);
    for (int i = 1; i <= n; i++) scanf("%d", x + i), pre[i] = pre[i - 1] + x[i];
    vector<int> q(n + 2);
    int l = 1, r = 1;
    q[0] = 0;
    for (int i = 1; i <= n; i++) {
        ll tmp = 2 * a * pre[i];
        while (l < r && slope(q[l], q[l + 1]) > tmp) l++;
        int k = q[l];
        tmp = pre[i] - pre[k];
        dp[i] = dp[k] + a * tmp * tmp + b * tmp + c;
        while (l < r && slope(q[r - 1], q[r]) < slope(q[r], i)) r--;
        q[++r] = i;
    }
    printf("%lld\n", dp[n]);
}