#include <bits/stdc++.h>
using namespace std;
const int maxn = 5e4 + 5;
vector<int> G[maxn];

struct LCA {
    int dep[maxn];      // depth
    int par[maxn][20];  // ancestor

    void init(int rt, int n) {
        dep[rt] = 0;
        dfs(rt, -1);

        for (int j = 1; j < 20; j++) {
            for (int i = 0; i < n; i++) {
                int v = par[i][j - 1];
                if (v == -1)
                    par[i][j] = -1;
                else
                    par[i][j] = par[v][j - 1];
            }
        }
    }

    void dfs(int u, int fa) {
        dep[u] = dep[fa] + 1;
        par[u][0] = fa;
        for (auto& v : G[u]) {
            if (v == fa) continue;
            dfs(v, u);
        }
    }

    int lca(int u, int v) {
        if (dep[u] > dep[v]) swap(u, v);
        for (int i = 19; i >= 0; i--)
            if (par[v][i] != -1 && dep[par[v][i]] >= dep[u])
                v = par[v][i];  // jump to the same depth

        if (u == v) return u;
        for (int i = 19; i >= 0; i--)
            if (par[u][i] != par[v][i])
                u = par[u][i], v = par[v][i];  // jump up together
        return par[u][0];
    }
} lca;

int w[maxn], ans;

void dfs(int u, int fa) {
    for (auto& v : G[u]) {
        if (v == fa) continue;
        dfs(v, u);
        w[u] += w[v];
    }
    ans = max(ans, w[u]);
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0, u, v; i < n - 1; i++) {
        scanf("%d%d", &u, &v);
        u--, v--;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    lca.init(0, n);
    for (int i = 0, u, v; i < m; i++) {
        scanf("%d%d", &u, &v);
        u--, v--;
        int Lca = lca.lca(u, v);
        w[u]++, w[v]++, w[Lca]--;
        if (lca.par[Lca][0] != -1) w[lca.par[Lca][0]]--;
    }
    ans = 0;
    dfs(0, -1);
    printf("%d\n", ans);
}