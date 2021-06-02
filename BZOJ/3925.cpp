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
const int maxn = 1 << 11;
const int maxm = 46;
ll con[maxn][maxm], disc[maxn][maxm], edges[maxn], C[maxm][maxm];
int G[15][15];
void init() {
    C[0][0] = 1;
    for (int i = 1; i < maxm; i++) {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; j++) C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
    }
}
int main() {
    // /*
#ifndef ONLINE_JUDGE
    freopen("1.in", "r", stdin);
    freopen("2.out", "w", stdout);
#endif
    // */
    std::ios::sync_with_stdio(false);
    init();
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0, u, v; i < m; i++) {
        scanf("%d%d", &u, &v);
        --u, --v;
        G[u][v] = G[v][u] = 1;
    }
    int S = 1 << n;
    for (int i = 0; i < S; i++)
        for (int j = 0; j < n; j++)
            if (i & (1 << j))
                for (int k = j + 1; k < n; k++)
                    if (i & (1 << k)) edges[i] += G[j][k];
    for (int i = 1, s; i < S; i++) {
        if (__builtin_popcount(i) == 1) {  // 集合里只有一个点
            con[i][0] = 1;
            continue;
        }
        s = i & (-i);
        for (int sub = i & (i - 1); sub; sub = (sub - 1) & i)
            if (sub & s)
                for (int j = 0; j <= edges[sub]; j++)
                    for (int k = 0; k <= edges[i ^ sub]; k++)
                        disc[i][j + k] += con[sub][j] * C[edges[i ^ sub]][k];
        for (int j = 0; j <= edges[i]; j++)
            con[i][j] = C[edges[i]][j] - disc[i][j];
    }
    double ans = 0;
    for (int i = 1; i <= m; i++)
        ans += 1.0 * con[S - 1][i] / C[edges[S - 1]][i];
    ans /= (m + 1);
    ans = 1.0 * con[S - 1][m] / C[edges[S - 1]][m] - ans;
    printf("%.6lf\n", ans);
}
