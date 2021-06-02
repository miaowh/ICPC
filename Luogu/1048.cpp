#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e3 + 5;
int a[maxn], b[maxn];
int dp[maxn];
int main() {
  int n, m;
  scanf("%d%d", &m, &n);
  for (int i = 1; i <= n; i++) scanf("%d%d", a + i, b + i);

  memset(dp, 0, sizeof(dp));
  for (int i = 1; i <= n; i++) {
    for (int j = m; j >= a[i]; j--) {
      dp[j] = max(dp[j], dp[j - a[i]] + b[i]);
    }
  }
  printf("%d\n", dp[m]);
}