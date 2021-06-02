#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 2e5 + 5;
vector<int> G[maxn];
set<int> unvis;
ll remain;

struct Dsu {
    vector<int> par;
    Dsu(int n) {
        par.resize(n);
        iota(par.begin(), par.end(), 0);
    }
    int find(int x) { return x == par[x] ? x : par[x] = find(par[x]); }
    void unite(int x, int y) {
        x = find(x), y = find(y);
        if (x != y) par[x] = y;
    }
    bool same(int x, int y) { return find(x) == find(y); }
};

void dfs(int u, Dsu &dsu) {
    unvis.erase(u);
    sort(G[u].begin(), G[u].end());
    for (int v = 1;;) {
        auto it = unvis.lower_bound(v);
        if (it == unvis.end()) return;
        v = *it;
        if (binary_search(G[u].begin(), G[u].end(), v) == false) {
            dsu.unite(u, v);
            dfs(v, dsu);
            remain--;
        }
        v++;
    }
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    remain = 1LL * n * (n - 1) / 2 - m;
    vector<array<int, 3>> edges;
    int xors = 0;
    for (int i = 0, u, v, w; i < m; i++) {
        scanf("%d%d%d", &u, &v, &w);
        G[u].push_back(v);
        G[v].push_back(u);
        edges.push_back({w, u, v});
        xors ^= w;
    }
    Dsu all(n + 1), assigned(n + 1);
    for (int i = 1; i <= n; i++) unvis.insert(i);
    for (int i = 1; i <= n; i++) {
        if (unvis.find(i) != unvis.end()) dfs(i, all);
    }
    if (remain > 0) xors = 0;

    ll ans = 0;
    sort(edges.begin(), edges.end());
    for (auto [w, u, v] : edges) {
        if (all.same(u, v) == false) {
            all.unite(u, v);
            ans += w;
            assigned.unite(u, v);
        } else if (assigned.same(u, v) == false) {
            assigned.unite(u, v);
            xors = min(xors, w);
        }
    }
    printf("%lld\n", ans + xors);
}