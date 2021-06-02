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
const int maxn = 1 << 21;
const int mod = 1e9 + 7;
ll a[20][20], all[maxn], dp[maxn];
int main() {
//	/*
#ifndef ONLINE_JUDGE
    freopen("1.in", "r", stdin);
    freopen("1.out", "w", stdout);
#endif
    //	*/
    std::ios::sync_with_stdio(false);
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) scanf("%lld", &a[i][j]);
    for (int i = 1; i < (1 << n); i++) {
        all[i] = 1;
        for (int j = 0; j < n; j++)
            if (i & (1 << j))
                for (int k = j + 1; k < n; k++)
                    if (i & (1 << k)) all[i] = all[i] * (a[j][k] + 1) % mod;
        int s;
        for (int j = n - 1; j >= 0; j--)
            if (i & (1 << j)) {
                s = j;
                break;
            }
        dp[i] = all[i];
        s = i ^ (1 << s);
        for (int j = s; j; j = (j - 1) & s) {
            dp[i] = (dp[i] - all[j] * dp[i ^ j] % mod + mod) % mod;
        }
    }
    printf("%lld\n", dp[(1 << n) - 1]);
}