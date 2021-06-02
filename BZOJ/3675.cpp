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
#define my_sort_unique(c) (random_shuffle(c.begin(), c.end())), my_unique(c)
const double PI = acos(-1.0);
const int INF = 0x3f3f3f3f;
const int NINF = 0xc0c0c0c0;
const int maxn = 1e5 + 5;
int a[maxn];
ll pre[maxn], dp[2][maxn];

// inline double slope(int j, int k, int i) {
//   double mj = dp[(i & 1) ^ 1][j] - pre[j] * pre[j];
//   double mk = dp[(i & 1) ^ 1][k] - pre[k] * pre[k];
//   if (pre[j] == pre[k]) return (mj - mk) > 0 ? 10000 : -1e9 - 5;
//   return (mj - mk) / (pre[j] - pre[k]);
// }

bool check1(int j, int k, int i, int t) {
  ll mj = dp[(i & 1) ^ 1][j] - pre[j] * pre[j];
  ll mk = dp[(i & 1) ^ 1][k] - pre[k] * pre[k];
  return (mj - mk) <= pre[t] * (pre[k] - pre[j]);
}
bool check2(int j, int k, int f, int i) {
  ll mj = dp[(i & 1) ^ 1][j] - pre[j] * pre[j];
  ll mk = dp[(i & 1) ^ 1][k] - pre[k] * pre[k];
  ll mf = dp[(i & 1) ^ 1][f] - pre[f] * pre[f];
  return (mj - mk) * (pre[f] - pre[k]) >= (mk - mf) * (pre[k] - pre[j]);
}
int main() {
  /*
#ifndef ONLINE_JUDGE
freopen("1.in", "r", stdin);
freopen("1.out", "w", stdout);
#endif
  */
  std::ios::sync_with_stdio(false);
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) scanf("%d", a + i), pre[i] = pre[i - 1] + a[i];
  for (int i = 1; i <= m; i++) {
    int l = 1, r = 1;
    vector<int> q(n + 2);
    q[1] = i - 1;
    for (int t = i; t <= n; t++) {
      while (l < r && check1(q[l], q[l + 1], i, t)) l++;
      int idx = q[l];
      dp[i & 1][t] = dp[(i & 1) ^ 1][idx] + pre[idx] * (pre[t] - pre[idx]);
      while (l < r && check2(q[r - 1], q[r], t, i)) r--;
      //   while (l < r && slope(q[r - 1], q[r], i) < slope(q[r], t, i)) r--;
      q[++r] = t;
    }
  }
  printf("%lld\n", dp[m & 1][n]);
}