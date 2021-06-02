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
const int maxn = 1e5 + 5;
const int types = 100;
char line[10005];
int tot;
struct Trie {
    int sz;
    int ch[maxn][types], f[maxn], val[maxn];
    map<int, int> maps;
    void init() {
        maps.clear();
        sz = 0;
        newnode();
    }
    int newnode() {
        val[sz] = 0;
        memset(ch[sz], -1, sizeof(ch[sz]));
        return sz++;
    }
    int idx(char c) { return c - 0x20; }
    void insert(int id, const char* s) {
        int u = 0;
        for (int i = 0; s[i]; i++) {
            int c = idx(s[i]);
            if (ch[u][c] == -1) ch[u][c] = newnode();
            u = ch[u][c];
        }
        maps[u] = val[u] = id;
    }
    void build() {
        queue<int> q;
        for (int i = 0; i < 95; i++) {
            if (~ch[0][i])
                f[ch[0][i]] = 0, q.push(ch[0][i]);
            else
                ch[0][i] = 0;
        }
        while ((!q.empty())) {
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
    int query(int id, const char* s) {
        queue<int> q;
        int u = 0;
        for (int i = 0; s[i]; i++) {
            int c = idx(s[i]);
            u = ch[u][c];
            for (int j = u; j && ~val[j]; j = f[j]) {
                q.push(j);
                val[j] = -1;
            }
        }
        vector<int> ans;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            if (maps.find(u) == maps.end())
                val[u] = 0;
            else {
                val[u] = maps[u];
                ans.push_back(val[u]);
            }
        }
        if (ans.size()) {
            sort(ans.begin(), ans.end());
            tot++;
            printf("web %d:", id);
            for (auto& v : ans) printf(" %d", v);
            puts("");
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
    trie.init();
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%s", line);
        trie.insert(i, line);
    }
    trie.build();
    tot = 0;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%s", line);
        trie.query(i, line);
    }
    printf("total: %d\n", tot);
}