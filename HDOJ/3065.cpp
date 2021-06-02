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
const int maxn = 2e6 + 5;
const int N = 5e4 + 5;
char pat[1005][60], t[maxn];
int cnt[1005];

struct Trie {
    int sz, val[maxn], ch[maxn][100], f[maxn];
    int newnode() {
        memset(ch[sz], -1, sizeof(ch[sz]));
        val[sz] = 0;
        return sz++;
    }
    void init() {
        sz = 0;
        newnode();
    }
    int idx(char c) { return c - 0x20; }
    void insert(int id, const char *s) {
        int u = 0;
        for (int i = 0, c; s[i]; i++) {
            c = idx(s[i]);
            if (ch[u][c] == -1) ch[u][c] = newnode();
            u = ch[u][c];
        }
        val[u] = id;
    }
    void build() {
        queue<int> q;
        int u = 0;
        f[u] = u;
        for (int i = 0; i < 95; i++) {
            if (~ch[u][i])
                f[ch[u][i]] = 0, q.push(ch[u][i]);
            else
                ch[u][i] = 0;
        }
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int i = 0; i < 95; i++) {
                if (~ch[u][i])
                    f[ch[u][i]] = ch[f[u]][i], q.push(ch[u][i]);
                else
                    ch[u][i] = ch[f[u]][i];
            }
        }
    }
    void query(const char *s) {
        memset(cnt, 0, sizeof(cnt));
        int u = 0;
        for (int i = 0, c; s[i]; i++) {
            c = idx(s[i]);
            u = ch[u][c];
            for (int j = u; j; j = f[j]) {
                if (val[j]) cnt[val[j]]++;
            }
        }
    }
} trie;
int main() {
//	/*
#ifndef ONLINE_JUDGE
    freopen("1.in", "r", stdin);
    freopen("1.out", "w", stdout);
#endif
    //	*/
    std::ios::sync_with_stdio(false);
    int n;
    while (~scanf("%d", &n)) {
        trie.init();
        for (int i = 1; i <= n; i++) {
            scanf("%s", pat[i]);
            trie.insert(i, pat[i]);
        }
        trie.build();
        scanf("%s", t);
        trie.query(t);
        for (int i = 1; i <= n; i++)
            if (cnt[i]) printf("%s: %d\n", pat[i], cnt[i]);
    }
}