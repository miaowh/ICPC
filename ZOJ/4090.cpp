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
const int maxn = 1e5 + 5;
int a[maxn], b[maxn];
int solve(vector<int> &l, vector<int> &h) {
    int ret = 0, p = 0;
    for (int i = 0; i < l.size(); i++) {
        if (p < h.size() && l[i] >= h[p]) {
            ret++;
            p++;
        }
    }
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
    scanf("%d", &T);
    while (T--) {
        int n, m;
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n; i++) scanf("%d", a + i);
        for (int i = 0; i < m; i++) scanf("%d", b + i);
        vector<int> bh, bl, gh, gl;
        for (int i = 0, x; i < n; i++) {
            scanf("%d", &x);
            if (x == 0)
                bl.push_back(a[i]);
            else
                bh.push_back(a[i]);
        }
        for (int i = 0, x; i < m; i++) {
            scanf("%d", &x);
            if (x == 0)
                gl.push_back(b[i]);
            else
                gh.push_back(b[i]);
        }
        sort(bl.begin(), bl.end());
        sort(gl.begin(), gl.end());
        sort(bh.begin(), bh.end());
        sort(gh.begin(), gh.end());
        int ans = solve(bl, gh) + solve(gl, bh);
        printf("%d\n", ans);
    }
}