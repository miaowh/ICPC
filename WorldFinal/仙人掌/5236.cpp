#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
const int maxn = 1e5;
vector<pii> G[maxn], BF[maxn];
int dfsClock, low[maxn], dfn[maxn], par[maxn];
int n, m, q;

void solve(int u, int v, int w) {}

void tarjan(int u, int fa) {
    par[u] = fa;
    dfn[u] = low[u] = ++dfsClock;
    for (auto &[v, w] : G[u]) {
        if (!dfn[v]) {
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

int main() {
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 0, u, v, w; i < m; i++) {
        scanf("%d%d%d", &u, &v, &q);
    }
    tarjan(1, 0);

    for (int i = 0, u, v; i < q; i++) {
        scanf("%d%d", &u, &v);
    }
}