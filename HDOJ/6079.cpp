#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 5, sqrt_maxn = 350;

int n, m, K, sz, vsz, a[maxn];
int L[sqrt_maxn], R[sqrt_maxn];
int fa[maxn];
int vblock[maxn];  // 每个值所属的值域块
int sumBlock[sqrt_maxn][sqrt_maxn];
int sumVal[sqrt_maxn][maxn];
int rt[sqrt_maxn][maxn];   // 第i块中，值为j的第一次出现的位置
int cnt[sqrt_maxn][maxn];  // 第i块中，值为j的个数
int c[maxn], s[sqrt_maxn];

int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }

int stk[maxn];
void update(int id, int l, int r, int x, int y) {
  int tmp = 0, top = 0;
  rt[id][x] = rt[id][y] = 0;
  for (int i = L[id]; i <= R[id]; i++) {
    a[i] = a[find(i)];
    if (a[i] == x || a[i] == y) stk[++top] = i;
  }
  // 不能合并到上面，因为 find() 会改变
  for (int i = l; i <= r; i++)
    if (a[i] == x) a[i] = y, ++tmp;
  for (int i = 1, t, w; i <= top; i++) {
    fa[stk[i]] = stk[i];
    t = stk[i], w = a[t];
    if (!rt[id][w])
      rt[id][w] = t;
    else
      fa[t] = rt[id][w];
  }

  cnt[id][x] -= tmp, cnt[id][y] += tmp;
  for (int i = id; i <= K; i++) {
    sumVal[i][x] -= tmp;
    sumVal[i][y] += tmp;
    if (vblock[x] != vblock[y])
      sumBlock[i][vblock[x]] -= tmp, sumBlock[i][vblock[y]] += tmp;
  }
}

inline void count(int l, int r, int w) {
  for (int i = l; i <= r; i++) {
    a[i] = a[find(i)];
    c[a[i]] += w;
    s[vblock[a[i]]] += w;
  }
}
int main() {
  int T;
  scanf("%d", &T);
  sz = 600;
  vsz = 400;
  for (int i = 1; i < maxn; i++) vblock[i] = (i + vsz - 1) / vsz;
  while (T--) {
    scanf("%d%d", &n, &m);
    memset(cnt, 0, sizeof(cnt));
    memset(rt, 0, sizeof(rt));

    K = (n + sz - 1) / sz;
    for (int i = 1; i <= n; i++) scanf("%d", a + i), fa[i] = i;
    for (int i = 1; i <= K; i++) {
      L[i] = (i - 1) * sz + 1, R[i] = min(n, i * sz);
      for (int j = 1; j <= vsz; j++) sumBlock[i][j] = sumBlock[i - 1][j];
      for (int j = 1; j < maxn; j++) sumVal[i][j] = sumVal[i - 1][j];
      for (int j = L[i]; j <= R[i]; j++) {
        if (!rt[i][a[j]])
          rt[i][a[j]] = j;
        else
          fa[j] = rt[i][a[j]];
        ++sumBlock[i][vblock[a[j]]];
        ++sumVal[i][a[j]];
        ++cnt[i][a[j]];
      }
    }
    for (int _ = 0, op, l, r, x, y; _ < m; _++) {
      scanf("%d%d%d", &op, &l, &r);
      int lb = (l + sz - 1) / sz, rb = (r + sz - 1) / sz;
      if (op == 1) {
        scanf("%d%d", &x, &y);
        if (x == y) continue;
        if (lb == rb)
          update(lb, l, r, x, y);
        else {
          update(lb, l, R[lb], x, y);
          update(rb, L[rb], r, x, y);
          int pre = 0;
          for (int i = lb + 1; i < rb; i++) {
            if (rt[i][x]) {
              if (!rt[i][y])
                rt[i][y] = rt[i][x], a[rt[i][x]] = y;
              else
                fa[rt[i][x]] = rt[i][y];
              rt[i][x] = 0;
              pre += cnt[i][x];
              cnt[i][y] += cnt[i][x];
              cnt[i][x] = 0;
            }
            sumVal[i][x] -= pre, sumVal[i][y] += pre;
            if (vblock[x] != vblock[y])
              sumBlock[i][vblock[x]] -= pre, sumBlock[i][vblock[y]] += pre;
          }
          for (int i = rb; i <= K; i++) {
            sumVal[i][x] -= pre, sumVal[i][y] += pre;
            if (vblock[x] != vblock[y])
              sumBlock[i][vblock[x]] -= pre, sumBlock[i][vblock[y]] += pre;
          }
        }
      } else {
        scanf("%d", &x);
        int sum = 0, ll, rr;
        if (lb == rb) {
          count(l, r, 1);
          for (int i = 1; i <= vsz; i++) {
            sum += s[i];
            if (sum >= x) {
              sum -= s[i];
              ll = (i - 1) * vsz + 1, rr = i * vsz;
              break;
            }
          }
          for (int i = ll; i <= rr; i++) {
            sum += c[i];
            if (sum >= x) {
              printf("%d\n", i);
              break;
            }
          }
          count(l, r, -1);
          continue;
        }
        count(l, R[lb], 1);
        count(L[rb], r, 1);
        for (int i = 1; i <= vsz; i++) {
          sum += s[i] + sumBlock[rb - 1][i] - sumBlock[lb][i];
          if (sum >= x) {
            sum -= s[i] + sumBlock[rb - 1][i] - sumBlock[lb][i];
            ll = (i - 1) * vsz + 1;
            rr = i * vsz;
            break;
          }
        }
        for (int i = ll; i <= rr; i++) {
          sum += c[i] + sumVal[rb - 1][i] - sumVal[lb][i];
          if (sum >= x) {
            printf("%d\n", i);
            break;
          }
        }
        count(l, R[lb], -1);
        count(L[rb], r, -1);
      }
    }
  }
}
