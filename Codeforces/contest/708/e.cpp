#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 5;
int a[maxn];
int le[maxn][25], dp[maxn][25];

int simplify(int x) {
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) {
            int cnt = 0;
            while (x % i == 0) {
                x /= i;
                cnt++;
            }
            if (cnt & 1) x *= i;
        }
    }
    return x;
}
int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n, k;
        scanf("%d%d", &n, &k);
        for (int i = 1, u; i <= n; i++) {
            scanf("%d", &u);
            u = simplify(u);
            a[i] = u;
        }
        map<int, int> last;
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= k; j++) {
                le[i][j] = le[i - 1][j];
                if (last.count(a[i])) {
                    if (j)
                        le[i][j] =
                            max(le[i][j], min(le[i - 1][j - 1], last[a[i]]));
                    else
                        le[i][j] = max(le[i][j], last[a[i]]);
                }
            }
            last[a[i]] = i;
        }
        for (int i = 0; i <= n; i++)
            for (int j = 0; j <= k; j++) dp[i][j] = 0x3f3f3f3f;
        for (int i = 0; i <= k; i++) dp[0][i] = 0;

        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= k; j++) {
                if (j) dp[i][j] = dp[i][j - 1];
                for (int t = 0; t <= j; t++) {
                    int l = le[i][t];
                    dp[i][j] = min(dp[i][j], dp[l][j - t] + 1);
                }
            }
        }

        printf("%d\n", dp[n][k]);
    }
}
