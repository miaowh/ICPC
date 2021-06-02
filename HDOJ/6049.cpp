#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
const int maxn = 3e3 + 5;
int dp[maxn][maxn], nxt[maxn], a[maxn];
int Min[maxn][maxn], Max[maxn][maxn];

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
      scanf("%d", a + i);
      dp[i][i] = 1;
      nxt[i] = i;
      Max[i][i] = Min[i][i] = a[i];
    }
    for (int i = 1; i <= n; i++) {
      for (int j = i + 1; j <= n; j++) {
        Min[i][j] = min(Min[i][j - 1], a[j]);
        Max[i][j] = max(Max[i][j - 1], a[j]);
      }
    }
    for (int len = 2; len <= n; len++) {
      for (int i = 1, j; i <= n - len + 1; i++) {
        j = i + len - 1;
        if (Max[i][j] - Min[i][j] + 1 != len)
          dp[i][j] = 0;
        else {
          if (Min[i][j] < Min[i][nxt[i]])
            dp[i][j] = 1;
          else
            dp[i][j] = dp[i][nxt[i]] + dp[nxt[i] + 1][j];
          nxt[i] = j;
        }
      }
    }
    vector<pii> vec;
    for (int i = 1; i <= n; i++) {
      for (int j = i; j <= n; j++) {
        if (Max[i][j] == j && Min[i][j] == i) {
          vec.push_back(make_pair(i, j));
          i = j;
          break;
        }
      }
    }
    int ans = vec.size();
    for (auto &V : vec) {
      int l = V.first;
      int r = V.second;
      for (int i = l; i < r; i++) {
        if (Max[l][i] - Min[l][i] == i - l && Max[l][i] == r) {
          for (int j = i + 1; j <= r; j++) {
            if (Max[j][r] - Min[j][r] == r - j && Min[j][r] == l) {
              ans = max(ans, int(vec.size()) + 1 + dp[i + 1][j - 1]);
            }
          }
        }
      }
    }
    printf("%d\n", ans);
  }
}