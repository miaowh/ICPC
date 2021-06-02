#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 1e6 + 5;
int a[maxn], pos[maxn];
int n, m;
ll k;
vector<pair<ll, ll>> fac;

ll exgcd(ll a, ll b, ll &x, ll &y) {
    if (a == 0 && b == 0) return -1;  // 无最大公因数
    ll d = a;
    if (b)
        d = exgcd(b, a % b, y, x), y -= x * (a / b);
    else
        x = 1, y = 0;
    return d;
}

bool excrt(vector<ll> r, vector<ll> m, ll &re, ll &M) {
    ll x, y;
    M = m[0], re = r[0];
    for (int i = 1; i < r.size(); i++) {
        ll d = exgcd(M, m[i], x, y);
        if ((r[i] - re) % d != 0) return 0;
        x = (r[i] - re) / d * x % (m[i] / d);
        re += x * M;
        M = M / d * m[i];
        re %= M;
    }
    re = (re + M) % M;
    return 1;
}

bool ok(ll val) {
    ll sum = 0;
    for (auto &v : fac) sum += max(0LL, (val - v.first + v.second) / v.second);
    return val + 1 - sum >= k;
}

int main() {
    scanf("%d%d%lld", &n, &m, &k);
    for (int i = 0; i < n; i++) scanf("%d", a + i), pos[a[i]] = -1;
    for (int i = 0, x; i < m; i++) {
        scanf("%d", &x);
        pos[x] = i;
    }
    vector<ll> mods = {n, m};
    for (int i = 0; i < n; i++) {
        int j = pos[a[i]];
        if (j == -1) continue;
        vector<ll> re = {i, j};
        ll a, b;
        if (excrt(re, mods, a, b)) {
            fac.push_back({a, b});
        }
    }

    ll l = 0, r = 1e18, ans;
    while (l <= r) {
        ll mid = l + r >> 1;
        if (ok(mid)) {
            ans = mid;
            r = mid - 1;
        } else
            l = mid + 1;
    }
    printf("%lld\n", ans + 1);
}
