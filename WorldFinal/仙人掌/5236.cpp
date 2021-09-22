#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
const int maxn = 1e5;
vector<pii> G[maxn], BF[maxn];
int dfsClock, low[maxn], dfn[maxn], par[maxn];
int n, m, q, tot;
int dep[maxn], dis[maxn];
int cir[maxn], toU[maxn];
bool vis[maxn];
void solve(int u, int v, int w) {
    vector<int> a;
    int sum = w;
    for (int i = v; i != u; i = par[i]) {
        sum += dis[i] - dis[par[i]];
        a.push_back(i);
    }
    a.push_back(u);
    cir[++tot] = sum;

    for (int i = a.size() - 1, pw = 0; i >= 0; i--) {
        toU[a[i]] = min(pw, sum - pw);
        BF[a[i]].push_back({tot, toU[a[i]]});
        BF[tot].push_back({a[i], toU[a[i]]});
        vis[a[i]] = pw <= sum - pw;
        if (i > 0) pw += dis[a[i - 1]] - dis[a[i]];
    }
}

void tarjan(int u, int fa) {
    par[u] = fa;
    dfn[u] = low[u] = ++dfsClock;
    dep[u] = dep[fa] + 1;
    for (auto &[v, w] : G[u]) {
        if (!dfn[v]) {
            dis[v] = dis[u] + w;
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
        } else if (v != fa)
            low[u] = min(low[u], dfn[v]);
        if (low[v] > dfn[u]) {
            BF[u].push_back({v, w});
            BF[v].push_back({u, w});
        }
    }
    for (auto &[v, w] : G[u]) {
        if (par[v] != u && dfn[v] > dfn[u]) {
            solve(u, v, w);
        }
    }
}

const int EXP = 25;
struct LCA {
    int par[maxn][EXP];
    int dep[maxn];
    int dis[maxn];

    void work(int n) {
        dep[1] = 0;
        dfs(1, -1);

        for (int i = 1; i < EXP; i++) {
            for (int j = 1; j <= n; j++) {
                int tmp = par[j][i - 1];
                if (tmp != -1)
                    par[j][i] = par[tmp][i - 1];
                else
                    par[j][i] = -1;
            }
        }
    }
    void dfs(int u, int fa) {
        par[u][0] = fa;
        for (auto &[v, w] : BF[u]) {
            if (v == fa) continue;
            dep[v] = dep[u] + 1;
            dis[v] = dis[u] + w;
            dfs(v, u);
        }
    }
    int lca(int u, int v) {
        int uu = u, vv = v;
        if (dep[u] < dep[v]) swap(u, v);
        // 先跳到同一高度
        for (int i = EXP - 1; i >= 0; i--) {
            int tmp = par[u][i];
            if (tmp == -1 || dep[v] > dep[tmp]) continue;
            u = tmp;
        }
        if (u == v) {
            return abs(dis[uu] - dis[vv]);
        }
        // 一起向上跳
        for (int i = EXP - 1; i >= 0; i--) {
            if (par[u][i] != par[v][i]) {
                u = par[u][i];
                v = par[v][i];
            }
        }
        int fa = par[u][0];
        if (fa <= n) return dis[uu] + dis[vv] - 2 * dis[fa];
        int ret = dis[uu] - dis[u] + dis[vv] - dis[v];
        if (vis[u] == vis[v])
            ret += min(abs(toU[u] - toU[v]), cir[fa] - abs(toU[u] - toU[v]));
        else
            ret += min(toU[u] + toU[v], cir[fa] - toU[u] - toU[v]);
        return ret;
    }
} lca;

int main() {
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 0, u, v, w; i < m; i++) {
        scanf("%d%d%d", &u, &v, &w);
        G[u].push_back({v, w});
        G[v].push_back({u, w});
    }
    tot = n;
    tarjan(1, 0);
    lca.work(tot);

    for (int i = 0, u, v; i < q; i++) {
        scanf("%d%d", &u, &v);
        printf("%d\n", lca.lca(u, v));
    }
}
