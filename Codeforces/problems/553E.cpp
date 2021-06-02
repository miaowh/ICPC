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
const double PI = acos(-1.0);
const int INF = 0x3f3f3f3f;
const int NINF = 0xc0c0c0c0;
const int maxn = 55;
const int N = 2e4 + 5;
int a[maxn], b[maxn], c[maxn];
int dis[maxn][maxn];
double p[maxn][N], sum[maxn][N], dp[maxn][N];
int n, m, t, x;

namespace fft {
typedef double db;

struct cp {
    db x, y;
    cp() { x = y = 0; }
    cp(db x, db y) : x(x), y(y) {}
};

inline cp operator+(cp a, cp b) { return cp(a.x + b.x, a.y + b.y); }
inline cp operator-(cp a, cp b) { return cp(a.x - b.x, a.y - b.y); }
inline cp operator*(cp a, cp b) {
    return cp(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x);
}
inline cp conj(cp a) { return cp(a.x, -a.y); }

int base = 1;
vector<cp> roots = {{0, 0}, {1, 0}};
vector<int> rev = {0, 1};

const db PI = acosl(-1.0);

void ensure_base(int nbase) {
    if (nbase <= base) return;
    rev.resize(static_cast<unsigned long>(1 << nbase));
    for (int i = 0; i < (1 << nbase); i++)
        rev[i] = (rev[i >> 1] >> 1) + ((i & 1) << (nbase - 1));
    roots.resize(static_cast<unsigned long>(1 << nbase));
    while (base < nbase) {
        db angle = 2 * PI / (1 << (base + 1));
        for (int i = 1 << (base - 1); i < (1 << base); i++) {
            roots[i << 1] = roots[i];
            db angle_i = angle * (2 * i + 1 - (1 << base));
            roots[(i << 1) + 1] = cp(cos(angle_i), sin(angle_i));
        }
        base++;
    }
}

void fft(vector<cp>& a, int n = -1) {
    if (n == -1) n = a.size();
    assert((n & (n - 1)) == 0);
    int zeros = __builtin_ctz(n);
    ensure_base(zeros);
    int shift = base - zeros;
    for (int i = 0; i < n; i++)
        if (i < (rev[i] >> shift)) swap(a[i], a[rev[i] >> shift]);
    for (int k = 1; k < n; k <<= 1)
        for (int i = 0; i < n; i += 2 * k)
            for (int j = 0; j < k; j++) {
                cp z = a[i + j + k] * roots[j + k];
                a[i + j + k] = a[i + j] - z;
                a[i + j] = a[i + j] + z;
            }
}
vector<cp> fa, fb;
vector<int> multiply(vector<int>& a, vector<int>& b) {
    int need = a.size() + b.size() - 1;
    int nbase = 0;
    while ((1 << nbase) < need) nbase++;
    ensure_base(nbase);
    int sz = 1 << nbase;
    if (sz > (int)fa.size()) fa.resize(static_cast<unsigned long>(sz));
    for (int i = 0; i < sz; i++) {
        int x = (i < (int)a.size() ? a[i] : 0);
        int y = (i < (int)b.size() ? b[i] : 0);
        fa[i] = cp(x, y);
    }
    fft(fa, sz);
    cp r(0, -0.25 / sz);
    for (int i = 0; i <= (sz >> 1); i++) {
        int j = (sz - i) & (sz - 1);
        cp z = (fa[j] * fa[j] - conj(fa[i] * fa[i])) * r;
        if (i != j) {
            fa[j] = (fa[i] * fa[i] - conj(fa[j] * fa[j])) * r;
        }
        fa[i] = z;
    }
    fft(fa, sz);
    vector<int> res(static_cast<unsigned long>(need));
    for (int i = 0; i < need; i++) {
        res[i] = fa[i].x + 0.5;
    }
    return res;
}
};  // namespace fft

void solve(int l, int r) {
    if (l == r) {
        for (int i = 1; i <= m; i++)
            dp[a[i]][l] = min(dp[a[i]][l], sum[i][l] + c[i]);
        return;
    }
    int m = l + r >> 1;
    solve(m + 1, r);
    vector<double> f1, f2;
    for (int i = 1; i <= m; i++) {
    }
    solve(l, m);
}
int main() {
    //	/*
#ifndef ONLINE_JUDGE
    freopen("1.in", "r", stdin);
    freopen("1.out", "w", stdout);
#endif
    //	*/
    std::ios::sync_with_stdio(false);
    scanf("%d%d%d%d", &n, &m, &t, &x);
    clr(dis, 0x3f);
    for (int i = 1; i <= m; i++) {
        scanf("%d%d%d", &a[i], &b[i], &c[i]);
        dis[a[i]][b[i]] = c[i];
        for (int k = 1; k <= t; k++) {
            scanf("%lf", &p[i][k]);
        }
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            for (int k = 1; k <= n; k++)
                dis[j][k] = min(dis[j][k], dis[j][i] + dis[i][k]);
    for (int i = 1; i <= n; i++)
        for (int k = 0; k <= t; k++) dp[i][k] = 1e9;
    for (int i = 1; i <= n; i++) dp[i][t + 1] = x + dis[i][n];
    for (int i = 0; i <= t; i++) dp[n][i] = 0;
    clr(sum, 0);
    for (int i = 1; i <= m; i++) {
        double P = 0;
        for (int k = 1; k <= t; k++) {
            P += p[i][t - k + 1];
            sum[i][k] += P * dp[b[i]][t + 1];
        }
    }
    solve(0, t);
    printf("%.8lf\n", dp[1][0]);
}