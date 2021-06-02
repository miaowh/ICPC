// ybmj
#include <bits/stdc++.h>
using namespace std;
#define lson (rt << 1)
#define rson (rt << 1 | 1)
#define lson_len (len - (len >> 1))
#define rson_len (len >> 1)
#define pb(x) push_back(x)
#define clr(a, x) memset(a, x, sizeof(a))
#define mp(x, y) make_pair(x, y)
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
#define my_unique(a) a.resize(distance(a.begin(), unique(a.begin(), a.end())))
#define my_sort_unique(c) (sort(c.begin(), c.end())), my_unique(c)
const int INF = 0x3f3f3f3f;
const int NINF = 0xc0c0c0c0;
const double PI = acos(-1.0);
const int mod = 1e9 + 7;
const int maxn = 50;
ll ban[maxn], a[maxn];
int n, m;

ll Pow(ll a, ll b) {
    ll ret = 1;
    while (b) {
        if (b & 1) ret = ret * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return ret;
}
ll inv(ll a) { return Pow(a, mod - 2); }
ll squ(ll a) { return a * a % mod; }
ll dfs(ll x, ll S) {
    if (x == n) return 1;
    ll ret = dfs(x + 1, S);
    if (ban[x] == (1LL << x)) return S >> x & 1 ? ret : ret * (a[x] + 1) % mod;
    if ((S >> x & 1) == 0)
        ret = (ret + a[x] * dfs(x + 1, S | ban[x]) % mod) % mod;
    return ret;
}

int main() {
    // /*
#ifndef ONLINE_JUDGE
    freopen("1.in", "r", stdin);
    freopen("1.out", "w", stdout);
#endif
    // */
    std::ios::sync_with_stdio(false);
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) scanf("%lld", a + i), ban[i] = (1LL << i);
    for (int i = 0, u, v; i < m; i++) {
        scanf("%d%d", &u, &v);
        v--, u--;
        if (v > u) swap(v, u);
        ban[v] |= (1LL << u);
    }
    ll sum = dfs(0, 0LL);
    for (int i = 0; i < n; i++) a[i] = squ(a[i]);
    ll squ_sum = dfs(0, 0LL);
    for (int i = 0; i < n; i++) a[i] = 1;
    ll num = dfs(0, 0LL);
    // printf("%lld %lld %lld\n", sum, squ_sum, num);
    ll ans = (squ_sum + squ(sum) * inv(num) % mod -
              2LL * squ(sum) * inv(num) % mod + mod) %
             mod * inv(num) % mod;
    printf("%lld\n", ans);
}

/*
ybmj:

状态转移：$dfs(i, stat) = dfs(i+1, stat | ban[i]) \times a[i] + dfs(i+1, stat)$

当$stat >> i & 1$为$0$时才可以转移$dfs(i+1, stat | ban[i]) \times a[i]$

这样是$O(2^n)$

性质：当$i$为独立结点时，$dfs(i,stat) = dfs(i+1, stat) \times (a[i] + 1)$

所以尽可能的要把结点变为独立结点。考虑限制$u < v$，只建立一条单向边$u -> v$

这样当选择了$u$时，就没办法选择$v$，那么转移为$dfs(v,stat) = dfs(v+1, stat)$

如果没有选择$u$或其它能限制$v$的结点，并且$v$对后面的结点没有限制时，$v$就变成了独立结点。

如果没有选择$u$或其它能限制$v$的结点，并且$v$对后面的结点有限制，那么转移就是一开始的样子。

所以满足上面条件，会有两个转移状态的结点最多只有$\frac{n}{2}$，因为每有一个非独立节点，就要求前米有一个点没选，并且后面有点也不能选。
*/