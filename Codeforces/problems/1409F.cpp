#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
const int maxn = 300;
int dp[maxn][maxn][maxn];
char s[maxn], p[5];

int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    scanf("%s%s", s, p);
    memset(dp, 0xc0, sizeof(dp));
    dp[0][0][0] = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= k; j++) {
            for (int t = 0; t <= n; t++) {
                for (int c = 'a'; c <= 'z'; c++) {
                    int nj = c == s[i - 1] ? j : j + 1;
                    int nt = c == p[0] ? t + 1 : t;
                    dp[i][nj][nt] = max(dp[i][nj][nt],
                                        dp[i - 1][j][t] + (c == p[1] ? t : 0));
                }
            }
        }
    }
    int ans = 0;
    for (int i = 0; i <= k; i++) {
        for (int j = 0; j <= n; j++) {
            ans = max(ans, dp[n][i][j]);
        }
    }
    printf("%d\n", ans);
}