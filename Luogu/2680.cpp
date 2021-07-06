#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
using ll = long long;
const int maxn = 3e5 + 5;
int n, m;
vector<pii> G[maxn];
vector<pii> pairs;
int a[maxn];
ll cost[maxn], pcost[maxn];

const int EXP = 25;
struct LCA {
    int par[maxn][EXP];
    int dep[maxn];
    void init() {
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
        for (auto &[v, w] : G[u]) {
            if (v == fa) continue;
            dep[v] = dep[u] + 1;
            dfs(v, u);
        }
    }
    int lca(int u, int v) {
        if (dep[u] < dep[v]) swap(u, v);
        for (int i = EXP - 1; i >= 0; i--) {
            int anc = par[u][i];
            if (anc == -1 || dep[anc] < dep[v]) continue;
            u = anc;
        }
        if (u == v) return u;
        for (int i = EXP - 1; i >= 0; i--) {
            if (par[u][i] != par[v][i]) {
                u = par[u][i];
                v = par[v][i];
            }
        }
        return par[u][0];
    }
} lca;

void dfsCost(int u, int fa) {
    for (auto &[v, w] : G[u]) {
        if (v == fa) continue;
        cost[v] = cost[u] + w;
        dfsCost(v, u);
    }
}

int isn[maxn], ew[maxn];

void dfsIsn(int u, int fa) {
    for (auto &[v, w] : G[u]) {
        if (v == fa) continue;
        ew[v] = w;
        dfsIsn(v, u);
        isn[u] += isn[v];
    }
}
bool check(ll val) {
    for (int i = 0; i < n; i++) isn[i] = 0;

    int cnt = 0;
    ll mx = 0;
    for (int i = 0; i < m; i++) {
        if (pcost[i] > val) {
            isn[pairs[i].first]++;
            isn[pairs[i].second]++;
            isn[a[i]] -= 2;
            cnt++;
            mx = max(mx, pcost[i]);
        }
    }
    if (cnt == 0) return true;
    dfsIsn(0, -1);

    for (int i = 0; i < n; i++) {
        if (isn[i] == cnt) {
            if (mx - ew[i] <= val) return true;
        }
    }
    return false;
}

int main() {
    scanf("%d%d", &n, &m);
    ll l = 0, r = 0;
    for (int i = 0, u, v, t; i < n - 1; i++) {
        scanf("%d%d%d", &u, &v, &t);
        --u, --v;
        G[u].push_back({v, t});
        G[v].push_back({u, t});
        r += t;
    }
    lca.init();
    dfsCost(0, -1);
    for (int i = 0, u, v; i < m; i++) {
        scanf("%d%d", &u, &v);
        --u, --v;
        pairs.push_back({u, v});
        a[i] = lca.lca(u, v);
        pcost[i] = cost[u] + cost[v] - 2 * cost[a[i]];
        // printf("%d %lld\n", a[i], pcost[i]);
    }
    ll ans = -1;
    while (l <= r) {
        ll mid = l + r >> 1;
        if (check(mid)) {
            ans = mid;
            r = mid - 1;
        } else
            l = mid + 1;
    }
    printf("%lld\n", ans);
}