// dp[i][j][2] 将[i,j]合并后的最小值与最大值。
// dp[i][j][0] =

#include <bits/stdc++.h>
using namespace std;
const int maxn = 205;
int dp[maxn][maxn][2];
int pre[maxn], a[maxn];

inline int sum(int l, int r) { return pre[r] - pre[l - 1]; }

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) scanf("%d", a + i), a[i + n] = a[i];
  if (n == 1) {
    printf("%d\n%d\n", 0, 0);
    return 0;
  }
  for (int i = 1; i <= 2 * n; i++) pre[i] = pre[i - 1] + a[i];
  int ans[2] = {0x3f3f3f3f, -1};
  for (int d = 1; d <= n; d++) {
    for (int i = 1, j = i + d - 1; i <= 2 * n; i++, j++) {
      if (d == 1) {
        dp[i][j][0] = dp[i][j][1] = 0;
        continue;
      }
      dp[i][j][0] = 0x3f3f3f3f, dp[i][j][1] = -1;
      for (int k = i; k < j && k <= 2 * n; k++) {
        dp[i][j][0] =
            min(dp[i][k][0] + dp[k + 1][j][0] + sum(i, j), dp[i][j][0]);
        dp[i][j][1] =
            max(dp[i][k][1] + dp[k + 1][j][1] + sum(i, j), dp[i][j][1]);
      }
      if (d == n && i <= n) {
        ans[0] = min(ans[0], dp[i][j][0]);
        ans[1] = max(ans[1], dp[i][j][1]);
      }
    }
  }

  printf("%d\n%d\n", ans[0], ans[1]);
}