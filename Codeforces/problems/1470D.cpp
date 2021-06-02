#include <bits/stdc++.h>
using namespace std;
const int maxn = 3e5 + 5;
vector<int> G[maxn];
int color[maxn];

void dfs(int u, int c) {
    if (c == 1) {
        for (auto &v : G[u]) {
            if (color[v] == c) {
                c = -c;
                break;
            }
        }
    }
    color[u] = c;
    for (auto &v : G[u]) {
        if (color[v] == 0) {
            dfs(v, -c);
        }
    }
}

bool work(int n) {
    dfs(1, 1);
    vector<int> ans;
    for (int i = 1; i <= n; i++) {
        if (color[i] == 0) return false;
        if (color[i] == 1) ans.push_back(i);
    }
    puts("YES");
    printf("%d\n", ans.size());
    for (auto &v : ans) printf("%d ", v);
    puts("");
    return true;
}
/*
 不连通 No
 否则 YEs
*/
int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n, m;
        scanf("%d%d", &n, &m);
        for (int i = 0, u, v; i < m; i++) {
            scanf("%d%d", &u, &v);
            G[u].push_back(v);
            G[v].push_back(u);
        }
        if (work(n) == false) puts("NO");
        for (int i = 1; i <= n; i++) color[i] = 0, G[i].clear();
    }
}