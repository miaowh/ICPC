#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 5;
const int sqrt_maxn = 505;
int a[maxn], am[maxn];
int n, q, m, mm;
int blockSize = 350;

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

int LB[sqrt_maxn], RB[sqrt_maxn];

inline void pd(int id) {  // pushdown
  int l = LB[id], r = RB[id];
  for (int i = l; i < r; i++) {
    if (a[i] != fh[id][c[i]]) {
      a[i] = fh[id][c[i]];
      am[i] = a[i] / blockSize;
    }
  }
}
inline void change(int bl, int x, int y) {
  int id = h[bl][x];
  h[bl][y] = id;
  fh[bl][id] = y;
  h[bl][x] = 0;  // 没有出现
}
inline void build(int id) {
  int tp = 0;
  for (int i = 1; i <= blockSize; i++) h[id][fh[id][i]] = 0;
  for (int i = LB[id]; i < RB[id]; i++) {
    if (!h[id][a[i]]) {
      h[id][a[i]] = ++tp;
      fh[id][tp] = a[i];
    }
  }
  for (int i = LB[id]; i < RB[id]; i++) c[i] = h[id][a[i]];
}
int main() {
  scanf("%d%d", &n, &q);
  m = n / blockSize + 1;      // [0,m)块数
  mm = maxn / blockSize + 1;  // 值域块数

  for (int i = 0; i < sqrt_maxn; i++) {
    LB[i] = i * blockSize;
    RB[i] = min(n, (i + 1) * blockSize);
  }

  for (int i = 0; i < n; i++) scanf("%d", a + i), am[i] = a[i] / blockSize;
  for (int i = 0; i < m; i++) build(i);

  for (int i = 0; i < m; i++) {
    if (i) {
      for (int j = 0; j < maxn; j++) {
        cnt[i][j] = cnt[i - 1][j];
      }
    }
    if (i) {
      for (int j = 0; j < mm; j++) {
        b[i][j] = b[i - 1][j];
      }
    }
    for (int j = LB[i]; j < RB[i]; j++) {
      cnt[i][a[j]]++;
      b[i][am[j]]++;
    }
  }
  for (int _ = 0, op, l, r, x, y; _ < q; _++) {
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
  scanf("%d%d", &n, &m);
  sz = 600;
  vsz = 400;
  K = (n + sz - 1) / sz;
  for (int i = 1; i <= n; i++) scanf("%d", a + i), fa[i] = i;
  for (int i = 1; i < maxn; i++) vblock[i] = (i + vsz - 1) / vsz;
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
      int bl = l / blockSize, br = r / blockSize;
      int bx = x / blockSize, by = y / blockSize;
      if (cnt[br][x] - (bl ? cnt[bl - 1][x] : 0) == 0)
        continue;  // [l,r] 中没有值为x的数
      for (int i = m - 1; i >= 1 && i >= bl; i--) {
        cnt[i][x] -= cnt[i - 1][x];  // 第i块中，值为x的数量
        cnt[i][y] -= cnt[i - 1][y];
        b[i][bx] -= b[i - 1][bx];  // 第i块中，值在第bx块的数量
        b[i][by] -= b[i - 1][by];
      }
      if (bl == br) {
        pd(bl);
        for (int i = l; i <= r; i++) {
          if (a[i] == x) {
            a[i] = y;
            am[i] = y / blockSize;
            cnt[bl][x]--;
            cnt[bl][y]++;
            b[bl][bx]--;
            b[bl][by]++;
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
        build(bl);
      } else {
        pd(bl), pd(br);
        for (int i = l; i < RB[bl]; ++i) {
          if (a[i] == x) {
            a[i] = y, cnt[bl][x]--, cnt[bl][y]++, b[bl][bx]--, b[bl][by]++;
            am[i] = y / blockSize;
          }
        }
        for (int i = LB[br]; i <= r; ++i) {
          if (a[i] == x) {
            a[i] = y, cnt[br][x]--, cnt[br][y]++, b[br][bx]--, b[br][by]++;
            am[i] = y / blockSize;
          }
        }
        build(bl), build(br);

        for (int i = bl + 1; i < br; i++) {
          if (cnt[i][x]) {
            if (cnt[i][y]) {
              pd(i);
              for (int j = LB[i]; j < RB[i]; ++j) {
                if (a[j] == x) {
                  a[j] = y, cnt[i][x]--, cnt[i][y]++, b[i][bx]--, b[i][by]++;
                  am[j] = y / blockSize;
                }
              }
              build(i);
            } else {
              b[i][by] += cnt[i][x];
              b[i][bx] -= cnt[i][x];
              cnt[i][y] += cnt[i][x];
              cnt[i][x] = 0;
              change(i, x, y);
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
      for (int i = max(1, bl); i < m; i++) {
        cnt[i][x] += cnt[i - 1][x];
        cnt[i][y] += cnt[i - 1][y];
        b[i][bx] += b[i - 1][bx];
        b[i][by] += b[i - 1][by];
      }
    } else {
      scanf("%d", &x);
      int bl = l / blockSize, br = r / blockSize;
      if (bl == br) {
        pd(bl);
        for (int i = l; i <= r; i++) ls[i] = a[i];
        nth_element(ls + l, ls + l + x - 1, ls + r + 1);
        printf("%d\n", ls[l + x - 1]);
        for (int i = l; i <= r; i++) ls[i] = 0;
      } else {
        pd(bl), pd(br);
        for (int i = l; i < RB[bl]; i++) {
          ls[a[i]]++;
          ls2[am[i]]++;
        }
        for (int i = LB[br]; i <= r; i++) {
          ls[a[i]]++;
          ls2[am[i]]++;
        }
        for (int i = 0, sum = 0; i < mm; i++) {
          if (ls2[i] + b[br - 1][i] - b[bl][i] + sum >= x) {
            for (int j = i * blockSize; j < min(maxn, (i + 1) * blockSize);
                 j++) {
              if (ls[j] + cnt[br - 1][j] - cnt[bl][j] + sum >= x) {
                printf("%d\n", j);
                goto out;
              } else {
                sum += ls[j] + cnt[br - 1][j] - cnt[bl][j];
              }
            }
          } else {
            sum += ls2[i] + b[br - 1][i] - b[bl][i];
          }
        }
      out:
        for (int i = l; i < RB[bl]; i++) {
          ls[a[i]]--;
          ls2[am[i]]--;
        }
        for (int i = LB[br]; i <= r; i++) {
          ls[a[i]]--;
          ls2[am[i]]--;
        }
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