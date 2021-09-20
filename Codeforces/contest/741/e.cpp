#include <bits/stdc++.h>
using namespace std;
const int maxn = 5e3 + 5;
struct SA {
    char s[maxn];
    int sa[maxn], t[maxn], t2[maxn], c[maxn], rank[maxn], height[maxn];
    int dp[maxn][30];
    void build(int m, int n) {  // [0,m-1]字符集, [0,n-1] 字符串
        n++;
        int *x = t, *y = t2;
        for (int i = 0; i < m; i++) c[i] = 0;
        for (int i = 0; i < n; i++) c[x[i] = s[i]]++;
        for (int i = 1; i < m; i++) c[i] += c[i - 1];
        for (int i = n - 1; ~i; i--) sa[--c[x[i]]] = i;
        for (int k = 1; k <= n; k <<= 1) {
            int p = 0;
            for (int i = n - k; i < n; i++) y[p++] = i;
            for (int i = 0; i < n; i++)
                if (sa[i] >= k) y[p++] = sa[i] - k;
            for (int i = 0; i < m; i++) c[i] = 0;
            for (int i = 0; i < n; i++) c[x[y[i]]]++;
            for (int i = 1; i < m; i++) c[i] += c[i - 1];
            for (int i = n - 1; ~i; i--) sa[--c[x[y[i]]]] = y[i];
            swap(x, y);
            p = 1;
            x[sa[0]] = 0;
            for (int i = 1; i < n; i++)
                x[sa[i]] =
                    y[sa[i - 1]] == y[sa[i]] && y[sa[i - 1] + k] == y[sa[i] + k]
                        ? p - 1
                        : p++;
            if (p >= n) break;
            m = p;
        }
        n--;
        int k = 0;
        for (int i = 0; i <= n; i++) rank[sa[i]] = i;
        for (int i = 0; i < n; i++) {
            if (k) k--;
            int j = sa[rank[i] - 1];
            while (s[i + k] == s[j + k]) k++;
            height[rank[i]] = k;
        }
    }
    void initRmq(int n) {
        for (int i = 1; i <= n; i++) dp[i][0] = height[i];
        for (int j = 1; (1 << j) <= n; j++)
            for (int i = 1; i + (1 << j) - 1 <= n; i++)
                dp[i][j] = min(dp[i][j - 1], dp[i + (1 << (j - 1))][j - 1]);
    }
    int rmq(int l, int r) {
        int k = 31 - __builtin_clz(r - l + 1);
        return min(dp[l][k], dp[r - (1 << k) + 1][k]);
    }
    int lcp(int a, int b) {
        // 返回起始地址为a和b的两个后缀串的lcp
        a = rank[a], b = rank[b];
        if (a > b) swap(a, b);
        return rmq(a + 1, b);
    }
} sa;

int dp[maxn];

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d%s", &n, sa.s);
        sa.build(200, n);
        sa.initRmq(n);
        int ans = 0;
        for (int i = 0; i < n; i++) {
            dp[i] = n - i;
            for (int j = i - 1; j >= 0; j--) {
                int x = sa.lcp(i, j);
                if (x < n - i && sa.s[i + x] > sa.s[j + x])
                    dp[i] = max(dp[i], dp[j] + n - i - x);
            }
            ans = max(ans, dp[i]);
        }
        printf("%d\n", ans);
    }
}