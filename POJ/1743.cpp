#include <algorithm>
#include <cstdio>
using namespace std;
const int INF = 0x3f3f3f3f;
const int NINF = 0xc0c0c0c0;
const int maxn = 4e4 + 4;
int a[maxn];
struct SA {
    int s[maxn];
    int sa[maxn], t[maxn], t2[maxn], c[maxn], rank[maxn], height[maxn];
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
            height[rank[i]] = k;  // h[i] = height[rank[i]]
        }
    }
    int dp[maxn][30];
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
        // 返回两个后缀的最长公共前缀
        a = rank[a], b = rank[b];
        if (a > b) swap(a, b);
        return rmq(a + 1, b);
    }
} sa;

int par[maxn], Max[maxn], Min[maxn];

int find(int u) { return par[u] == u ? u : par[u] = find(par[u]); }
void merge(int u, int v) {
    u = find(u);
    v = find(v);
    if (u == v) return;
    par[u] = v;
}
bool ok(int x, int n) {
    for (int i = 1; i <= n; i++) par[i] = i, Max[i] = NINF, Min[i] = INF;
    for (int i = 2; i <= n; i++) {
        if (sa.height[i] >= x) {
            merge(i - 1, i);
        }
    }
    for (int i = 1, tmp; i <= n; i++) {
        tmp = find(i);
        Max[tmp] = max(sa.sa[i], Max[tmp]);
        Min[tmp] = min(sa.sa[i], Min[tmp]);
    }
    for (int i = 1; i <= n; i++)
        if (par[i] == i && Max[i] - Min[i] >= x) return true;
    return false;
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("1.in", "r", stdin);
    freopen("1.out", "w", stdout);
#endif
    int n;
    while (~scanf("%d", &n)) {
        if (!n) break;
        for (int i = 0; i < n; i++) scanf("%d", a + i);
        a[n] = 300;
        for (int i = 0; i < n; i++) {
            sa.s[i] = a[i + 1] - a[i] + 500;
        }
        sa.s[n] = 0;
        sa.build(1000, n);
        int l = 4, r = n, ans = -1;
        while (l <= r) {
            int mid = l + r >> 1;
            if (ok(mid, n)) {
                ans = mid;
                l = mid + 1;
            } else
                r = mid - 1;
        }
        printf("%d\n", ++ans);
    }
}