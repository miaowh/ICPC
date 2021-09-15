#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 5;
vector<int> G[maxn];

int dfsClock = 0;
int par[maxn], dfn[maxn], low[maxn];
int dp[maxn][2];
void tarjan(int u, int fa) {
    par[u] = fa;
    dfn[u] = low[u] = ++dfsClock;
    dp[u][0] = 0, dp[u][1] = 1;

    for (auto &v : G[u]) {
        if (!dfn[v]) {
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
        } else if (v != fa)
            low[u] = min(low[u], dfn[v]);
        if (low[v] < dfn[u]) {
            dp[u][1] += dp[v][0];
            dp[u][0] += max(dp[v][0], dp[v][1]);
        }
    }

    for (auto &v : G[u]) {
        if (par[v] != u && dfn[v] > dfn[u]) {
            int f0 = 0, f1 = 0;
            int t0 = 0, t1 = 0;
            for (int i = v; i != u; i = par[i]) {
                t0 = f1 + dp[i][0];
                t1 = f0 + dp[i][1];
                f1 = max(t0, t1);
                f0 = t0;
            }
            dp[u][0] += f1;
            f0 = 0, f1 = -1e9;
            for (int i = v; i != u; i = par[i]) {
                t0 = f1 + dp[i][0];
                t1 = f0 + dp[i][1];
                f1 = max(t0, t1);
                f0 = t0;
            }
            dp[u][1] += f0;
        }
    }
}
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0, u, v; i < m; i++) {
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    tarjan(1, 0);
    printf("%d\n", max(dp[1][0], dp[1][1]));
}