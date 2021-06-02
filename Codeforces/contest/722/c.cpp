#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 5;
int p[maxn][2];
vector<int> G[maxn];
using ll = long long;
ll dp[maxn][2];
bool vis[maxn];

void dfs(int u) {
    vis[u] = true;
    for (auto &v : G[u]) {
        if (vis[v] == true) continue;
        dfs(v);
        dp[u][0] += max(abs(p[u][0] - p[v][0]) + dp[v][0],
                        abs(p[u][0] - p[v][1]) + dp[v][1]);
        dp[u][1] += max(abs(p[u][1] - p[v][0]) + dp[v][0],
                        abs(p[u][1] - p[v][1]) + dp[v][1]);
    }
}
void work() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        vis[i] = 0, dp[i][0] = dp[i][1] = 0, G[i].clear();
    for (int i = 0; i < n; i++) scanf("%d%d", &p[i][0], &p[i][1]);
    for (int i = 0, u, v; i < n - 1; i++) {
        scanf("%d%d", &u, &v);
        u--, v--;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    dfs(0);
    printf("%lld\n", max(dp[0][0], dp[0][1]));
}
int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        work();
    }
}