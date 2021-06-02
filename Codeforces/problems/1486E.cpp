#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
const int maxn = 1e5 + 5;
vector<pii> G[maxn];
int dp[maxn][51];

void dij(int s) {
    memset(dp, 0x3f, sizeof(dp));
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push({0, s});
    dp[s][0] = 0;
    while (!pq.empty()) {
        auto now = pq.top();
        pq.pop();
        int u = now.second, w = now.first;
        int num = u % 51;
        u /= 51;
        if (dp[u][num] < w) continue;
        int v, vw;
        for (auto &p : G[u]) {
            tie(v, vw) = p;
            int numv = num ? 0 : vw;
            int val = num ? (vw + num) * (vw + num) : 0;
            if (dp[v][numv] > dp[u][num] + val) {
                dp[v][numv] = dp[u][num] + val;
                pq.push({dp[v][numv], v * 51 + numv});
            }
        }
    }
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0, u, v, w; i < m; i++) {
        scanf("%d%d%d", &u, &v, &w);
        u--, v--;
        G[u].push_back({v, w});
        G[v].push_back({u, w});
    }
    dij(0);
    for (int i = 0; i < n; i++) {
        if (dp[i][0] == 0x3f3f3f3f) dp[i][0] = -1;
        printf("%d ", dp[i][0]);
    }
}

/*
因为权值大小只有50，考虑将每个点拆成51个点。
dp[u][i] 表示u点接收了权值为i的边后，得到的答案。

当i为0时，就表示是原来的点，
当i>0时，就表示是新拆的点。

然后就可以dij
*/