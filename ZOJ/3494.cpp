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
#define my_sort_unique(c) (sort(c.begin(), c.end())), my_unique(c)
const int INF = 0x3f3f3f3f;
const int NINF = 0xc0c0c0c0;
const double PI = acos(-1.0);
const int maxn = 2005;
const int mod = 1e9 + 9;
char a[205], b[205], pat[205];
int c[205];
struct Tire {
    int ch[maxn][2], val[maxn], f[maxn], sz;
    int newnode() {
        memset(ch[sz], -1, sizeof(ch[sz]));
        val[sz] = 0;
        return sz++;
    }
    void init() {
        sz = 0;
        newnode();
    }
    int idx(const char &c) { return c - '0'; }
    void insert(const char *s) {
        int u = 0;
        for (int i = 0, c; s[i]; i++) {
            c = idx(s[i]);
            if (ch[u][c] == -1) ch[u][c] = newnode();
            u = ch[u][c];
        }
        val[u]++;
    }
    void build() {
        queue<int> q;
        f[0] = 0;
        for (int i = 0; i < 2; i++) {
            if (~ch[0][i])
                f[ch[0][i]] = 0, q.push(ch[0][i]);
            else
                ch[0][i] = 0;
        }
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            if (val[f[u]]) val[u]++;  // 优化
            for (int i = 0; i < 2; i++) {
                if (~ch[u][i])
                    f[ch[u][i]] = ch[f[u]][i], q.push(ch[u][i]);
                else
                    ch[u][i] = ch[f[u]][i];
            }
        }
    }
    int query(int u, int num) {
        for (int i = 3, c; i >= 0; i--) {
            c = (num & (1 << i)) ? 1 : 0;
            u = ch[u][c];
            for (int j = u; j; j = f[j]) {
                if (val[j]) return -1;
            }
        }
        return u;
    }
} trie;
int dp[205][2050];
int dfs(int pos, int stat, bool limit, bool zero) {
    if (stat == -1) return 0;
    if (pos < 0) return 1;
    if (!limit && ~dp[pos][stat] && !zero) return dp[pos][stat];
    int up = limit ? c[pos] : 9;
    int ret = 0;
    for (int i = 0; i <= up; i++) {
        if (i == 0 && zero) {
            ret += dfs(pos - 1, stat, limit && i == up, zero && !i);
        } else {
            int u = trie.query(stat, i);
            ret += dfs(pos - 1, u, limit && i == up, zero && !i);
        }
        ret %= mod;
    }
    if (!limit && !zero) dp[pos][stat] = ret;
    return ret;
}
int solve(const char *s) {
    int pos = 0;
    int sz = strlen(s);
    for (int i = 0; s[i]; i++) {
        c[pos++] = s[sz - i - 1] - '0';
    }
    return dfs(pos - 1, 0, true, true);
}
int main() {
    // /*
#ifndef ONLINE_JUDGE
    freopen("1.in", "r", stdin);
    freopen("1.out", "w", stdout);
#endif
    // */
    std::ios::sync_with_stdio(false);
    int T;
    scanf("%d", &T);
    while (T--) {
        trie.init();
        memset(dp, -1, sizeof(dp));
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%s", pat);
            trie.insert(pat);
        }
        trie.build();
        scanf("%s%s", a, b);
        for (int i = strlen(a) - 1; i >= 0; i--) {
            if (a[i] == '0') {
                a[i] = '9';
            } else {
                a[i]--;
                break;
            }
        }
        int ans = (solve(b) - solve(a) + mod) % mod;
        printf("%d\n", ans);
    }
}