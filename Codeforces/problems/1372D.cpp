#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 4e5 + 5;
ll a[maxn], suf[maxn][2];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%lld", a + i);
    for (int i = n; i < 2 * n; i++) a[i] = a[i - n];
    for (int i = 2 * n - 1; i >= 0; i--) {
        suf[i][0] = suf[i + 1][0];
        suf[i][1] = suf[i + 1][1];
        suf[i][i & 1] += a[i];
    }
    ll ans = 0;
    for (int i = 0; i < n; i++)
        ans = max(ans, suf[i][i & 1] - suf[i + n][i & 1]);
    printf("%lld\n", ans);
}