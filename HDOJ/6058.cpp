#include <bits/stdc++.h>
using namespace std;
const int maxn = 5e5 + 5;
int a[maxn], idx[maxn], pre[maxn], nxt[maxn];
void remove(int i) {
  nxt[pre[i]] = nxt[i];
  pre[nxt[i]] = pre[i];
}
int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int n, k;
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) {
      scanf("%d", a + i);
      idx[a[i]] = i;
      pre[i] = i - 1;
      nxt[i] = i + 1;
    }
    long long ans = 0;
    for (int i = 1; i <= n; i++) {
      vector<int> l, r;
      for (int j = idx[i]; j > 0 && l.size() < k; j = pre[j])
        l.push_back(j - pre[j]);
      for (int j = idx[i]; j <= n && r.size() < k; j = nxt[j])
        r.push_back(nxt[j] - j);
      for (int j = 0, t; j < k && j < l.size(); j++) {
        t = k - j - 1;
        if (t >= r.size()) continue;
        ans += 1LL * l[j] * r[t] * i;
      }
      remove(idx[i]);
    }
    printf("%lld\n", ans);
  }
}