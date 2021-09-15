// p4244
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5;
vector<int> G[maxn];

int dfsClock, dep[maxn];
int par[maxn], dfn[maxn], low[maxn];
int ans, dp[maxn];

void tarjan(int u, int fa) {
    par[u] = fa;
    dfn[u] = low[u] = ++dfsClock;
    dep[u] = dep[fa] + 1;

    for (auto &v : G[u]) {
        if (!dfn[v]) {
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
        } else if (v != fa)
            low[u] = min(low[u], dfn[v]);
        if (low[v] > dfn[u]) {
            ans = max(ans, dp[u] + dp[v] + 1);
            dp[u] = max(dp[u], dp[v] + 1);
        }
    }

    for (auto &v : G[u]) {
        if (par[v] != u && dfn[u] < dfn[v]) {
            vector<int> a;
            for (int i = v;; i = par[i]) {
                a.push_back(i);
                if (i == u) break;
            }
            int sz = a.size();
            for (int i = v;; i = par[i]) {
                a.push_back(i);
                if (i == u) break;
            }
            reverse(a.begin(), a.end());

            deque<int> dq;
            for (int i = 0; i < a.size(); i++) {
                while (!dq.empty() and (i - dq.front()) * 2 > sz)
                    dq.pop_front();
                if (!dq.empty())
                    ans =
                        max(ans, dp[a[i]] + dp[a[dq.front()]] + i - dq.front());
                while (!dq.empty() and
                       dp[a[i]] - i >= dp[a[dq.front()]] - dq.front())
                    dq.pop_back();
                dq.push_back(i);
            }

            for (int i = v; i != u; i = par[i]) {
                dp[u] = max(dp[u],
                            dp[i] + min(dep[i] - dep[u], 1 + dep[v] - dep[i]));
            }
        }
    }
}
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0, k; i < m; i++) {
        scanf("%d", &k);
        for (int j = 0, u = -1, v; j < k; j++) {
            scanf("%d", &v);
            if (u != -1) {
                G[u].push_back(v);
                G[v].push_back(u);
            }
            u = v;
        }
    }
    tarjan(1, 0);
    printf("%d\n", ans);
}