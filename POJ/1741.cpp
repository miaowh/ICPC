// ybmj
// #include <bits/stdc++.h>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <vector>
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
const int maxn = 1e4 + 5;
vector<pii> G[maxn];
int n, k, rt, treesz, son[maxn], sz[maxn];
bool vis[maxn];
vector<int> nodes;
ll ans;

void getRoot(int u, int fa) {
    sz[u] = 1, son[u] = 0;
    for (int i = 0; i < G[u].size(); i++) {
        int v = G[u][i].first;
        if (vis[v] || v == fa) continue;
        getRoot(v, u);
        sz[u] += sz[v];
        son[u] = max(son[u], sz[v]);
    }
    son[u] = max(son[u], treesz - sz[u]);
    if (son[u] < son[rt]) rt = u;
    // 调用时保证 son[rt] = INF, rt的初值不能和已有的点重合
}

void getSubTreeEle(int u, int fa, int val) {
    nodes.push_back(val);
    for (int i = 0; i < G[u].size(); i++) {
        int v = G[u][i].first;
        int w = G[u][i].second;
        if (v == fa || vis[v]) continue;
        if (val + w <= k) getSubTreeEle(v, u, val + w);
    }
}
int cal(int u, int w) {
    nodes.clear();
    getSubTreeEle(u, 0, w);
    sort(nodes.begin(), nodes.end());
    int l = 0, r = nodes.size() - 1;
    int ret = 0;
    while (l <= r) {
        while (r > l && nodes[r] + nodes[l] > k) r--;
        ret += r - l;
        l++;
    }
    return ret;
}

void dfs(int u) {
    ans += cal(u, 0);
    vis[u] = 1;
    for (int i = 0; i < G[u].size(); i++) {
        int v = G[u][i].first;
        int w = G[u][i].second;
        if (vis[v]) continue;
        ans -= cal(v, w);
        rt = 0, son[rt] = INF, treesz = sz[v];
        getRoot(v, u);
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
    // std::ios::sync_with_stdio(false);
    while (~scanf("%d%d", &n, &k)) {
        if (n == 0 && k == 0) return 0;
        for (int i = 0; i <= n; i++) G[i].clear(), vis[i] = 0;
        for (int i = 0, u, v, w; i < n - 1; i++) {
            scanf("%d%d%d", &u, &v, &w);
            G[u].push_back(make_pair(v, w));
            G[v].push_back(make_pair(u, w));
        }
        ans = 0;
        treesz = n, rt = 0, son[rt] = INF;
        getRoot(1, 0);
        dfs(rt);
        printf("%lld\n", ans);
    }
}