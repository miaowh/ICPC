#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = (5e5 + 5) * 30;
vector<int> a[maxn / 30];
ll ans;
struct Trie {
  int ch[maxn][2], val[maxn];
  int sz, rt;
  int newnode() {
    memset(ch[sz], -1, sizeof(ch[sz])), val[sz] = 0;
    return sz++;
  }
  void init() { sz = 0, rt = newnode(); }
  void update(vector<int> &num, int x) {
    int u = 0;
    for (int i = 0; i < num.size(); i++) {
      int c = num[i];
      if (ch[u][c] == -1) ch[u][c] = newnode();
      u = ch[u][c];
      val[u] += x;
    }
  }
} trie[2];
long long solve(vector<int> &num) {
  int u[2] = {0, 0};
  long long ret = 0;
  for (int i = 0; i < num.size(); i++) {
    int c = num[i];
    u[0] = trie[0].ch[u[0]][c];
    int tmp = trie[1].ch[u[1]][c ^ 1];
    if (u[0] != -1 && tmp != -1) {
      if (trie[0].val[u[0]] && trie[1].val[tmp]) {
        ret += 1LL * trie[0].val[u[0]] * trie[1].val[tmp];
      }
    }
    u[1] = trie[1].ch[u[1]][c];
    if (u[0] == -1 || u[1] == -1) break;
  }
  return ret;
}
int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int n;
    scanf("%d", &n);
    trie[0].init();
    trie[1].init();
    ans = 0;
    for (int i = 0, x; i < n; i++) {
      a[i].clear();
      scanf("%d", &x);
      for (int j = 30; j >= 0; j--) {
        if ((1 << j) & x) {
          x ^= (1 << j);
          a[i].push_back(1);
        } else
          a[i].push_back(0);
      }
      trie[1].update(a[i], 1);
    }
    trie[1].update(a[0], -1);
    for (int i = 1; i < n - 1; i++) {
      trie[0].update(a[i - 1], 1);
      trie[1].update(a[i], -1);
      ans += solve(a[i]);
    }
    printf("%lld\n", ans);
  }
}