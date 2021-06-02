#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        ll a, b, c, d;
        scanf("%lld%lld%lld%lld", &a, &b, &c, &d);
        if (a > b * c) {
            puts("-1");
            continue;
        }
        ll k = a / (b * d);
        ll ans = (k + 1) * a - k * (k + 1) / 2 * b * d;
        printf("%lld\n", ans);
    }
}