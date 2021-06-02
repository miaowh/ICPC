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
const int maxn = 1e6 + 6;
const int N = 1e5;
char s[maxn];
ll sum[maxn << 1];
int pos[maxn << 1], val[maxn << 1];

void build(int l, int r, int rt) {
    if (l == r) {
        pos[rt] = -1;
        val[rt] = l;
        return;
    }
    int m = l + r >> 1;
    build(l, m, lson);
    build(m + 1, r, rson);
    val[rt] = min(val[lson], val[rson]);
    sum[rt] = sum[lson] + sum[rson];
}
void update(int l, int r, int rt, int p, int x) {
    if (l == r) {
        pos[rt] = max(pos[rt], x);
        if (pos[rt] == -1)
            val[rt] = l;
        else
            val[rt] = INF;
        sum[rt] = pos[rt];
        return;
    }
    int m = l + r >> 1;
    if (p <= m)
        update(l, m, lson, p, x);
    else
        update(m + 1, r, rson, p, x);
    val[rt] = min(val[lson], val[rson]);
    sum[rt] = sum[lson] + sum[rson];
}
/*
int getPos(int l, int r, int rt, int p) {
    if (l == r) return pos[rt];
    int m = l + r >> 1;
    if (p <= m) return getPos(l, m, lson, p);
    return getPos(m + 1, r, rson, p);
}
*/
ll query(int l, int r, int rt, int p) {
    if (p >= r) {
        return sum[rt];
    }
    int m = l + r >> 1;
    ll ret = query(l, m, lson, p);
    if (p > m) ret += query(m + 1, r, rson, p);
    return ret;
}
int main() {
//	/*
#ifndef ONLINE_JUDGE
    freopen("1.in", "r", stdin);
    freopen("1.out", "w", stdout);
#endif
    //	*/
    std::ios::sync_with_stdio(false);
    int T;
    ll ten[5] = {1, 10, 100, 1000, 10000};
    scanf("%d", &T);
    while (T--) {
        scanf("%s", s);
        int n = strlen(s);
        build(1, N, 1);
        ll ans = 0;
        for (int i = 0, flag = INF; i < n; i++) {
            int res = 0;
            for (int j = 0; j < 5 && i - j >= 0; j++) {
                res += (s[i - j] - '0') * ten[j];
                if (res != 0) {
                    update(1, N, 1, res, i - j);
                    if (res == 1)
                        flag = INF;
                    else
                        flag = min(res - 1, flag);
                }
            }
            int tmp = val[1];
            if (tmp <= 1) {
                ans += i + 1;
                continue;
            }
            tmp = min(tmp - 1, flag);
            ans += tmp + 1 + query(1, N, 1, tmp) + i;
        }
        printf("%lld\n", ans);
    }
}
