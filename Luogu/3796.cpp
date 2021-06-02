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
const int maxn = 150 * 70 + 5;
const int N = 1e6 + 6;
char t[N], pat[155][100];
int cnt[155];

struct Trie {
    int ch[maxn][26], f[maxn], val[maxn];
    int sz, rt;
    int newnode() {
        memset(ch[sz], -1, sizeof(ch[sz])), val[sz] = 0;
        return sz++;
    }
    void init() { sz = 0, rt = newnode(); }
    int idx(char c) { return c - 'a'; }
    void insert(int id, const char* s) {
        int u = 0;
        for (int i = 0; s[i]; i++) {
            int c = idx(s[i]);
            if (ch[u][c] == -1) ch[u][c] = newnode();
            u = ch[u][c];
        }
        val[u] = id;
    }
    void build() {
        queue<int> q;
        f[rt] = rt;
        for (int c = 0; c < 26; c++) {
            if (~ch[rt][c])
                f[ch[rt][c]] = rt, q.push(ch[rt][c]);
            else
                ch[rt][c] = rt;
        }
        while (!q.empty()) {
            int u = q.front();
            // val[u] |= val[f[u]];
            q.pop();
            for (int c = 0; c < 26; c++) {
                if (~ch[u][c])
                    f[ch[u][c]] = ch[f[u]][c], q.push(ch[u][c]);
                else
                    ch[u][c] = ch[f[u]][c];
            }
        }
    }
    void query(int n, const char* s) {
        memset(cnt, 0, sizeof(cnt));
        int u = rt;
        for (int i = 0; s[i]; i++) {
            int c = idx(s[i]);
            u = ch[u][c];
            for (int j = u; j != rt; j = f[j]) {
                cnt[val[j]]++;
            }
        }
        int k = 1;
        for (int i = 1; i <= n; i++) {
            if (cnt[i] > cnt[k]) k = i;
        }
        printf("%d\n", cnt[k]);
        for (int i = 1; i <= n; i++) {
            if (cnt[i] == cnt[k]) printf("%s\n", pat[i]);
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
        if (n == 0) break;
        trie.init();
        for (int i = 1; i <= n; i++) {
            scanf("%s", pat[i]);
            trie.insert(i, pat[i]);
        }
        trie.build();
        scanf("%s", t);
        trie.query(n, t);
    }
}