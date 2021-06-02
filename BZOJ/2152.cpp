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
#define my_unique(a) a.resize(distance(a.begin(), unique(a.begin(), a.end())))
#define my_sort_unique(c) (sort(c.begin(), c.end())), my_unique(c)
const int INF = 0x3f3f3f3f;
const int NINF = 0xc0c0c0c0;
const double PI = acos(-1.0);
const int maxn = 1e5 + 5;
int rt, ans, treesz;
bool vis[maxn];
vector<pii> G[maxn];
int heavySonSz[maxn], sz[maxn], pre[maxn];

void getRoot(int u, int fa) {
    sz[u] = 1, heavySonSz[u] = 0;
    for (int i = 0; i < G[u].size(); i++) {
        int v = G[u][i].first;
        if (vis[v] || v == fa) continue;
        getRoot(v, u);
        sz[u] += sz[v];
        heavySonSz[u] = max(heavySonSz[u], sz[v]);
    }
    heavySonSz[u] = max(heavySonSz[u], treesz - sz[u]);
    if (heavySonSz[u] < heavySonSz[rt]) rt = u;
}

vector<int> nodes;
map<int, int> dp;

void dfsSub(int u, int fa, int val) {
    pre[u] = val % 3;
    dp[val % 3]++;
    nodes.push_back(u);
    for (int i = 0; i < G[u].size(); i++) {
        int v = G[u][i].first;
        int w = G[u][i].second;
        if (vis[v] || v == fa) continue;
        dfsSub(v, u, (val + w) % 3);
    }
}
int cal(int u, int val) {
    dp.clear();
    nodes.clear();
    dfsSub(u, 0, val);
    int ret = 0;
    for (int i = 0; i < nodes.size(); i++) {
        int v = nodes[i];
        int tmp = (3 - pre[v]) % 3;
        ret += dp[tmp];
    }
    return ret;
}
void dfs(int u) {
    vis[u] = 1;
    ans += cal(u, 0);
    for (int i = 0; i < G[u].size(); i++) {
        int v = G[u][i].first;
        if (vis[v]) continue;
        ans -= cal(v, G[u][i].second);
        treesz = sz[v], rt = 0, getRoot(v, u);
        dfs(rt);
    }
}
int main() {
//	/*
#ifndef ONLINE_JUDGE
    freopen("1.in", "r", stdin);
    freopen("1.out", "w", stdout);
#endif
    //	*/
    std::ios::sync_with_stdio(false);
    int n;
    scanf("%d", &n);
    for (int i = 0, u, v, w; i < n - 1; i++) {
        scanf("%d%d%d", &u, &v, &w);
        G[u].push_back(make_pair(v, w % 3));
        G[v].push_back(make_pair(u, w % 3));
    }
    ans = 0, treesz = n, rt = 0, heavySonSz[rt] = INF, getRoot(1, 0);
    dfs(rt);
    int mu = n * n;
    int d = __gcd(ans, mu);
    printf("%d/%d\n", ans / d, mu / d);
}