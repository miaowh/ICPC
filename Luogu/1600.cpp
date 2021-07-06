#include <bits/stdc++.h>
using namespace std;
const int maxn = 3e5 + 5;
vector<int> G[maxn];
int w[maxn];

const int EXP = 25;
struct LCA {
    int par[maxn][EXP];
    int dep[maxn];

    void work(int n) {
        dep[0] = 0;
        dfs(0, -1);
        for (int i = 1; i < EXP; i++) {
            for (int j = 0; j < n; j++) {
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
        for (auto &v : G[u]) {
            if (v == fa) continue;
            dep[v] = dep[u] + 1;
            dfs(v, u);
        }
    }
    int lca(int u, int v) {
        if (dep[u] < dep[v]) swap(u, v);
        // 先跳到同一高度
        for (int i = EXP - 1; i >= 0; i--) {
            int tmp = par[u][i];
            if (tmp == -1 || dep[v] > dep[tmp]) continue;
            u = tmp;
        }
        if (u == v) return u;
        // 一起向上跳
        for (int i = EXP - 1; i >= 0; i--) {
            if (par[u][i] != par[v][i]) {
                u = par[u][i];
                v = par[v][i];
            }
        }
        return par[u][0];
    }
} lca;

int ans[maxn];
vector<array<int, 3>> up[maxn], down[maxn];
map<int, int> upBucket, downBucket;

void dfs(int u, int fa) {
    for (auto &p : down[u]) {
        if (u == p[0]) downBucket[lca.dep[p[0]] - p[2]]++;
    }
    ans[u] += upBucket[lca.dep[u] + w[u]];
    ans[u] += downBucket[lca.dep[u] - w[u]];
    for (auto &p : up[u]) {
        if (u == p[1]) upBucket[lca.dep[p[0]]]++;
        if (u == p[0]) upBucket[lca.dep[p[0]]]--;
    }
    for (auto &p : down[u]) {
        if (u == p[1]) downBucket[lca.dep[p[0]] - p[2]]--;
    }
    for (auto &v : G[u]) {
        if (v == fa) continue;
        dfs(v, u);
    }
    ans[u] -= upBucket[lca.dep[u] + w[u]];
    ans[u] -= downBucket[lca.dep[u] - w[u]];
}
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0, u, v; i < n - 1; i++) {
        scanf("%d%d", &u, &v);
        --u, --v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    lca.work(n);

    for (int i = 0; i < n; i++) scanf("%d", w + i);
    for (int i = 0, u, v; i < m; i++) {
        scanf("%d%d", &u, &v);
        --u, --v;
        int Lca = lca.lca(u, v);
        up[u].push_back({u, Lca, 0});
        up[Lca].push_back({u, Lca, 0});
        int x = lca.dep[u] - lca.dep[Lca];
        if (Lca != v) down[Lca].push_back({Lca, v, x});
        down[v].push_back({Lca, v, x});
    }

    dfs(0, -1);

    for (int i = 0; i < n; i++) printf("%d ", ans[i]);
    puts("");
}

/*
将路径分为上行和下行两段，分别计数。
注意同一条路径的上行和下行可能都会对同一个观察点产生贡献，因此我选择在上行路径不计算终点的贡献。
统计子树前的答案减去统计子树后的答案。
*/