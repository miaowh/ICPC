#include <bits/stdc++.h>
using namespace std;
const int maxn = 40;
vector<int> G[maxn];
using ll = long long;
map<ll, int> ok;

int n, m;
void dfs1(int u, ll sta, int cnt) {
  if (u >= n / 2) {
    if (ok.find(sta) == ok.end())
      ok[sta] = cnt;
    else
      ok[sta] = min(ok[sta], cnt);  // !
    return;
  }
  dfs1(u + 1, sta, cnt);
  sta ^= (1LL << u);
  for (auto &v : G[u]) sta ^= (1LL << v);
  dfs1(u + 1, sta, cnt + 1);
}

int ans;
void dfs2(int u, ll sta, int cnt) {
  if (u >= n + 1) {
    ll tmp = 0;
    for (int i = 1; i <= n; i++) {
      if (sta & (1LL << i)) continue;
      tmp |= (1LL << i);
    }
    sta = tmp;
    if (ok.find(sta) != ok.end()) ans = min(ans, cnt + ok[sta]);
    return;
  }
  dfs2(u + 1, sta, cnt);
  sta ^= (1LL << u);
  for (auto &v : G[u]) sta ^= (1LL << v);
  dfs2(u + 1, sta, cnt + 1);
}
int main() {
  scanf("%d%d", &n, &m);
  for (int i = 0, u, v; i < m; i++) {
    scanf("%d%d", &u, &v);
    G[u].push_back(v);
    G[v].push_back(u);
  }
  ans = 1e9;
  dfs1(1, 0LL, 0);
  dfs2(n / 2, 0LL, 0);
  printf("%d\n", ans);
}