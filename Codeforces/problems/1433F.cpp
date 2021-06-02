#include <bits/stdc++.h>
using namespace std;
const int maxn = 100;
int mat[maxn][maxn], re[maxn][maxn], dp[maxn][maxn], tmp[maxn][maxn][maxn];

int main() {
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) scanf("%d", &mat[i][j]);
    memset(re, 0xc0, sizeof(re));
    re[0][0] = 0;

    for (int i = 1; i <= n; i++) {
        memset(tmp, 0xc0, sizeof(tmp));
        tmp[0][0][0] = 0;
        for (int j = 1; j <= m; j++) {
            for (int t = 0; t <= m / 2; t++) {
                for (int mod = 0; mod < k; mod++) {
                    tmp[j][t][mod] = tmp[j - 1][t][mod];
                    if (t > 0)
                        tmp[j][t][mod] = max(
                            tmp[j][t][mod],
                            tmp[j - 1][t - 1][(mod - mat[i][j] % k + k) % k] +
                                mat[i][j]);
                }
            }
        }
        for (int j = 0; j < k; j++) {
            for (int t = 0; t <= m / 2; t++) {
                re[i][j] = max(re[i][j], tmp[m][t][j]);
            }
        }
    }
    memset(dp, 0xc0, sizeof(dp));
    dp[0][0] = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < k; j++) {
            for (int t = 0; t < k; t++) {
                dp[i][j] = max(dp[i][j], dp[i - 1][t] + re[i][(j - t + k) % k]);
            }
        }
    }
    printf("%d\n", dp[n][0]);
}

/*
dp[i][j] 前i行，余数为j的最大值。

dp[i][j] = dp[i-1][t] + re[i][(j-t) % k]
*/