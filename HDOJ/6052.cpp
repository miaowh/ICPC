#include <bits/stdc++.h>
using namespace std;
const int maxn = 105;
int a[maxn][maxn];
int n, m;
typedef pair<int, int> pii;
typedef long long ll;
vector<pii> cpos[maxn * maxn];
set<int> color;

ll solve() {
  ll ans = 0;
  for (auto &v : color) {
    vector<int> b[maxn];
    for (auto &V : cpos[v]) {
      int r = V.first;
      int c = V.second;
      int lf = 0, rg = m - 1;
      for (int i = r; i >= 0; i--) {
        int id = upper_bound(b[i].begin(), b[i].end(), c) - b[i].begin();
        if (id == 0)
          lf = max(lf, 0);
        else {
          if (b[i][id - 1] == c) break;
          lf = max(lf, b[i][id - 1] + 1);
        }
        id = lower_bound(b[i].begin(), b[i].end(), c) - b[i].begin();
        if (id == b[i].size())
          rg = min(rg, m - 1);
        else {
          if (b[i][id] == c) break;
          rg = min(rg, b[i][id] - 1);
        }
        ans += (c - lf + 1) * (rg - c + 1) * (n - r);
      }
      b[r].push_back(c);
    }
  }
  return ans;
}
int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &m);
    color.clear();
    for (int i = 0; i < n * m; i++) cpos[i].clear();
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++) {
        scanf("%d", &a[i][j]);
        color.insert(a[i][j]);
        cpos[a[i][j]].push_back(make_pair(i, j));
      }
    for (auto &v : color) sort(cpos[v].begin(), cpos[v].end());
    ll tot = n * (n + 1) / 2 * m * (m + 1) / 2;
    double ans = 1.0 * solve() / tot;
    printf("%.9f\n", ans);
  }
}