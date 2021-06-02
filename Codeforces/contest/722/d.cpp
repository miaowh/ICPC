#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int mod = 998244353;
const int maxn = 1e6 + 6;
ll dp[maxn], pre[maxn];

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 2; i <= n * 2; i += 2) {
        for (int j = i; j <= 2 * n; j += i) {
            dp[j / 2]++;
        }
    }
    for (int i = 1; i <= n; i++) {
        dp[i] += pre[i - 1];
        dp[i] %= mod;
        pre[i] = pre[i - 1] + dp[i];
        pre[i] %= mod;
    }
    printf("%lld\n", dp[n]);
}