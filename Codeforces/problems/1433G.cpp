#include <bits/stdc++.h>
using namespace std;
using Edge = tuple<int, int, int>;
using pii = pair<int, int>;
const int maxn = 2e3;
vector<pii> G[maxn], path;
vector<Edge> edges;
int n, m, k;
int d[maxn][maxn];

void dij(int s) {
    for (int i = 0; i <= n; i++) d[s][i] = 1e9;
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push({0, s});
    d[s][s] = 0;
    while (!pq.empty()) {
        auto u = pq.top();
        pq.pop();
        if (d[s][u.second] < u.first) continue;
        for (auto &v : G[u.second]) {
            if (d[s][v.first] > u.first + v.second) {
                d[s][v.first] = u.first + v.second;
                pq.push({d[s][v.first], v.first});
            }
        }
    }
}

int main() {
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 0, u, v, w; i < m; i++) {
        scanf("%d%d%d", &u, &v, &w);
        G[u].push_back({v, w});
        G[v].push_back({u, w});
        edges.push_back({u, v, w});
    }
    for (int i = 0, u, v; i < k; i++) {
        scanf("%d%d", &u, &v);
        path.push_back({u, v});
    }
    for (int i = 1; i <= n; i++) dij(i);

    int ans = 1e9;
    for (auto &e : edges) {
        int sum = 0;
        for (auto &x : path)
            sum += min({d[x.first][x.second],
                        d[x.first][get<0>(e)] + d[get<1>(e)][x.second],
                        d[x.first][get<1>(e)] + d[get<0>(e)][x.second]});
        ans = min(ans, sum);
    }
    printf("%d\n", ans);
}