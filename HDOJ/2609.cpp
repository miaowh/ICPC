#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e4 + 5;
const int mod = 998244353;
char s[maxn][105];
char tmp[105];

int work(string s) {
  int n = s.size();
  int i, j, k;
  for (i = 0, j = 1, k = 0; i < n && j < n && k < n;) {
    if (s[(i + k) % n] == s[(j + k) % n])
      k++;
    else {
      if (s[(i + k) % n] > s[(j + k) % n])
        i = i + k + 1;
      else
        j = j + k + 1;
      if (i == j) i++;
      k = 0;
    }
  }
  return min(i, j);
}

int change(int id, int n) {
  int i, j, k;
  for (i = 0, j = 1, k = 0; i < n && j < n && k < n;) {
    if (s[id][(i + k) % n] == s[id][(j + k) % n])
      k++;
    else {
      if (s[id][(i + k) % n] > s[id][(j + k) % n])
        i = i + k + 1;
      else
        j = j + k + 1;
      if (i == j) i++;
      k = 0;
    }
  }
  int pos = min(i, j);
  int ret = 0, bias = 1;
  for (int i = 0; i < n; i++) {
    (ret += (s[id][(pos + i) % n] - '0' + 43) * bias % mod) %= mod;
    bias = bias * 1371LL % mod;
  }
  return ret;
}

int main() {
  int n;
  while (~scanf("%d", &n)) {
    for (int i = 0; i < n; i++) scanf("%s", s[i]);
    set<int> num;
    for (int i = 0; i < n; i++) num.insert(change(i, strlen(s[i])));
    printf("%d\n", num.size());
  }
}