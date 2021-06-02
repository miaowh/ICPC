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
const int maxn = 100;
const int maxc = 32005;
int c[maxn], w[maxn];
int dp[maxn][maxc];
vector<int> G[maxn];
int main() {
    //	/*
#ifndef ONLINE_JUDGE
    freopen("1.in", "r", stdin);
    freopen("1.out", "w", stdout);
#endif
    //	*/
    std::ios::sync_with_stdio(false);
    int V, m;
    scanf("%d%d", &V, &m);
    for (int i = 1, x; i <= m; i++) {
        scanf("%d%d%d", c + i, w + i, &x);
        G[x].pb(i);
    }
    for (int i = 1; i <= m; i++) {
        clr(dp[i], 0);
        for (int j = V; j >= c[i]; j--)
            dp[i][j] = dp[i][j - c[i]] + c[i] * w[i];
        for (int j = 0; j < c[i]; j++) dp[i][j] = NINF;
        for (auto &k : G[i]) {
            for (int j = V; j >= c[k]; j--)
                dp[i][j] = max(dp[i][j], dp[i][j - c[k]] + c[k] * w[k]);
        }
    }
    clr(dp[0], 0);
    for (auto &i : G[0]) {
        for (int j = V; j >= 0; j--) {
            for (int k = c[i]; k <= j; k++) {
                dp[0][j] = max(dp[0][j], dp[0][j - k] + dp[i][k]);
            }
        }
    }
    printf("%d\n", dp[0][V]);
}