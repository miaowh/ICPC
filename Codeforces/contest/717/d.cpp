#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 5;
int a[maxn], nxt[maxn], pos[maxn];
int dp[20][maxn];

vector<int> getPrime(int x) {
    vector<int> ret;
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) {
            ret.push_back(i);
            while (x % i == 0) x /= i;
        }
    }
    if (x != 1) ret.push_back(x);
    return ret;
}

int main() {
    int n, q;
    scanf("%d%d", &n, &q);
    for (int i = 0; i < n; i++) scanf("%d", a + i);

    memset(pos, -1, sizeof(pos));
    nxt[n] = n;
    for (int i = n - 1; i >= 0; i--) {
        auto pri = getPrime(a[i]);
        int mi = nxt[i + 1];
        for (auto &x : pri) {
            if (pos[x] != -1) mi = min(mi, pos[x]);
            pos[x] = i;
        }
        nxt[i] = mi;
    }
    for (int i = 0; i <= n; i++) dp[0][i] = nxt[i];
    for (int i = 1; i < 20; i++)
        for (int j = 0; j <= n; j++) dp[i][j] = dp[i - 1][dp[i - 1][j]];

    for (int i = 0, l, r; i < q; i++) {
        scanf("%d%d", &l, &r);
        l--, r--;
        int ans = 1;
        for (int j = 19; j >= 0; j--) {
            if (dp[j][l] == -1) continue;
            if (dp[j][l] > r) continue;
            ans += (1 << j);
            l = dp[j][l];
        }
        printf("%d\n", ans);
    }
}