// ybmj
#include <string.h>
#include <algorithm>
#include <cstdio>
#include <cstring>
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
#define my_sort_unique(c) (sort(c.begin(), c.end())), my_unique(c)
const int INF = 0x3f3f3f3f;
const int NINF = 0xc0c0c0c0;
const int maxn = 1000000 + 5;

struct SA {
    char s[maxn];
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
            height[rank[i]] = k;
        }
    }
    int dp[maxn];
    void initRmq(int n) {
        int k = rank[0];
        dp[k] = INF;
        for (int i = k + 1; i <= n; i++) dp[i] = min(dp[i - 1], height[i]);
        for (int i = k - 1; i >= 0; i--) dp[i] = min(dp[i + 1], height[i + 1]);
    }
    int lcp(int a, int b) {
        return dp[rank[b]];
        a = rank[a];
        b = rank[b];
        if (a > b) swap(a, b);
        int ans = INF;
        for (int i = a + 1; i <= b; i++) ans = min(ans, height[i]);
        return ans;
    }
} sa;

int main() {
    // /*
#ifndef ONLINE_JUDGE
    freopen("1.in", "r", stdin);
    freopen("1.out", "w", stdout);
#endif
    // */
    while (~scanf("%s", sa.s)) {
        if (sa.s[0] == '.') return 0;
        int n = strlen(sa.s);
        sa.build(300, n);
        sa.initRmq(n);
        for (int i = 0; i < n; i++) {
            if (n % (i + 1)) continue;
            if (sa.lcp(0, i + 1) == n - (i + 1)) {
                printf("%d\n", n / (i + 1));
                break;
            }
        }
    }
}