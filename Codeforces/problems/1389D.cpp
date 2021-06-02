

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n, m;
        scanf("%d%d", &n, &m);
        int al, ar, bl, br;
        scanf("%d%d%d%d", &al, &ar, &bl, &br);
        ll ans = 1e18;
        if (min(ar, br) > max(al, bl)) {
            ll rem = max(0LL, m - 1LL * n * (min(ar, br) - max(al, bl)));
            ll tot = 1LL * n * (abs(al - bl) + abs(ar - br));
            ans = min(rem, tot) + max(0LL, rem - tot) * 2LL;
        } else {
            ll cost = max(al, bl) - min(ar, br);
            ll len = max(ar, br) - min(al, bl);
            for (int i = 1; i <= n; i++) {
                ll tot =
                    min(ll(m), i * len) + cost * i + max(0LL, m - i * len) * 2;
                ans = min(ans, tot);
            }
        }
        printf("%lld\n", ans);
    }
}