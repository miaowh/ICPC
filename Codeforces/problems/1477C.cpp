#include <bits/stdc++.h>
using namespace std;
const int maxn = 5e3 + 5;
using ll = long long;
int x[maxn], y[maxn];
bool vis[maxn];

inline ll dis(int a, int b) {
    return 1LL * (x[a] - x[b]) * (x[a] - x[b]) +
           1LL * (y[a] - y[b]) * (y[a] - y[b]);
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d%d", x + i, y + i);
    vector<int> ans(n);
    ans[0] = 1;
    vis[1] = true;

    for (int i = 0; i < n - 1; i++) {
        int s = ans[i];
        int k = s;
        for (int j = 1; j <= n; j++) {
            if (vis[j]) continue;
            if (dis(s, k) < dis(s, j)) k = j;
        }
        vis[k] = true;
        ans[i + 1] = k;
    }

    for (auto &v : ans) printf("%d ", v);
}