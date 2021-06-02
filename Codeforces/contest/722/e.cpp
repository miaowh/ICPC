#include <bits/stdc++.h>
using namespace std;
const int maxn = 3e5 + 5;
using pii = pair<int, int>;
vector<int> G[2][maxn];
pii label[2][maxn];
int dfn, ans;
void dfsLabel(int u, int i) {
    label[i][u].first = dfn++;
    for (auto &v : G[i][u]) dfsLabel(v, i);
    label[i][u].second = dfn;
}

set<pii> fi, se;
int del[maxn];

void insert(int u) {
    // find ancestor
    auto it = se.upper_bound({label[1][u].first, 1e9});
    if (it != se.end()) {
        int le = label[1][it->second].first;
        if (label[1][u].first >= le) {
            del[u] = it->second;
            se.erase(it);
            se.insert({label[1][u].second, u});
            fi.erase(fi.lower_bound({le, -1}));
            fi.insert({label[1][u].first, u});
            return;
        }
    }
    // find son
    it = fi.lower_bound({label[1][u].first, -1});
    if (it == fi.end() or it->first >= label[1][u].second) {
        fi.insert({label[1][u].first, u});
        se.insert({label[1][u].second, u});
    }
}
void remove(int u) {
    auto it = fi.lower_bound({label[1][u].first, -1});
    if (it != fi.end() and it->second == u) {
        se.erase(se.find({label[1][u].second, u}));
        fi.erase(it);
    }
    if (del[u] != -1) {
        int v = del[u];
        fi.insert({label[1][v].first, v});
        se.insert({label[1][v].second, v});
    }
}
void dfs(int u) {
    insert(u);
    ans = max(ans, (int)fi.size());
    for (auto &v : G[0][u]) dfs(v);
    remove(u);
}
void work() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) del[i] = -1;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < 2; j++) G[j][i].clear();
    for (int i = 0; i < 2; i++) {
        for (int j = 1, u; j < n; j++) scanf("%d", &u), G[i][--u].push_back(j);
        dfn = 0;
        dfsLabel(0, i);
    }
    ans = 0;
    dfs(0);

    fi.clear(), se.clear();
    printf("%d\n", ans);
}
int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        work();
    }
}