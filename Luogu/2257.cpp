// ybmj
#include <bits/stdc++.h>
using namespace std;
#define lson (rt << 1)
#define rson (rt << 1 | 1)
#define lson_len (len - (len >> 1))
#define clr(a, x) memset(a, x, sizeof(a))
#define mp(x, y) make_pair(x, y)
using ll = long long;
using pii = pair<int, int>;
#define my_unique(a) a.resize(distance(a.begin(), unique(a.begin(), a.end())))
#define my_sort_unique(c) (sort(c.begin(), c.end())), my_unique(c)
const int INF = 0x3f3f3f3f;
const int NINF = 0xc0c0c0c0;
const double PI = acos(-1.0);
const int maxn = 1e7 + 5;
bool check[maxn];
int mu[maxn];
vector<int> prime;
void CalMu() {
    mu[1] = 1;
    for (int i = 2; i < maxn; i++) {
        if (!check[i]) prime.push_back(i), mu[i] = -1;
        for (int j = 0; j < prime.size(); j++) {
            ll nxt = 1ll * prime[j] * i;
            if (nxt >= maxn) break;
            check[nxt] = true;
            if (i % prime[j] == 0) {
                mu[nxt] = 0;
                break;
            } else
                mu[nxt] = -mu[i];
        }
    }
}

ll pre[maxn];
void init() {
    for (auto v : prime) {
        int tmp = v;
        for (; v < maxn; v += tmp) {
            pre[v] += mu[v / tmp];
        }
    }
    for (int i = 1; i < maxn; i++) pre[i] += pre[i - 1];
}

ll work(int n, int m) {
    ll ans = 0;
    for (int l = 1, r; l <= min(n, m); l = r + 1) {
        r = min(n / (n / l), m / (m / l));
        ans += 1ll * (n / l) * (m / l) * (pre[r] - pre[l - 1]);
    }
    return ans;
}
int main() {
//	/*
#ifndef ONLINE_JUDGE
    freopen("1.in", "r", stdin);
    freopen("1.out", "w", stdout);
#endif
    //	*/
    std::ios::sync_with_stdio(false);
    CalMu();
    init();
    int T;
    scanf("%d", &T);
    while (T--) {
        int n, m;
        scanf("%d%d", &n, &m);
        ll ans = work(n, m);
        printf("%lld\n", ans);
    }
}