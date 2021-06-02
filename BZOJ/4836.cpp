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
const int maxn = 5e4 + 5;

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
vector<cp> roots;
vector<int> rev;

const db PI = acosl(-1.0);
void init() {
    roots.pb(cp(0, 0));
    roots.pb(cp(1, 0));
    rev.pb(0);
    rev.pb(1);
}

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

vector<ll> multiply(vector<ll>& a, vector<ll>& b) {
    int need = a.size() + b.size() - 1;
    int nbase = 0;
    while ((1 << nbase) < need) nbase++;
    ensure_base(nbase);
    int sz = 1 << nbase;
    if (sz > (int)fa.size()) fa.resize(static_cast<unsigned long>(sz));
    for (int i = 0; i < sz; i++) {
        ll x = (i < (int)a.size() ? a[i] : 0);
        ll y = (i < (int)b.size() ? b[i] : 0);
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
    vector<ll> res(static_cast<unsigned long>(need));
    for (int i = 0; i < need; i++) {
        res[i] = fa[i].x + 0.5;
    }
    return res;
}
};  // namespace fft
ll a[maxn], b[maxn], c[maxn << 3];
const int offset = maxn;
void solve(int l, int r) {
    if (l == r) {
        c[0] += a[l] * b[r];
        return;
    }
    int m = l + r >> 1;
    vector<ll> s1(r - l + 1), s2(r - l + 1);
    for (int i = 0; i <= m - l; i++) s1[i] = a[i + l];
    for (int i = 1; i <= r - m; i++) s2[i] = b[i + m];
    vector<ll> ret = fft::multiply(s1, s2);
    for (int i = 1; i <= r - l; i++) c[i + l + m + offset] += ret[i];
    solve(l, m);
    solve(m + 1, r);
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("1.in", "r", stdin);
    freopen("1.out", "w", stdout);
#endif
    std::ios::sync_with_stdio(false);
    fft::init();
    int T;
    scanf("%d", &T);
    while (T--) {
        int n, m, q;
        scanf("%d%d%d", &n, &m, &q);
        clr(c, 0);
        clr(a, 0);
        clr(b, 0);
        for (int i = 0, x; i < n; i++) {
            scanf("%d", &x);
            a[x]++;
        }
        for (int i = 0, x; i < m; i++) {
            scanf("%d", &x);
            b[x]++;
        }
        vector<ll> s1(maxn), s2(maxn + offset);
        for (int i = 0; i < maxn; i++) s1[i] = a[i];
        for (int i = 0; i < maxn; i++) s2[offset - i] = b[i];
        vector<ll> ret = fft::multiply(s1, s2);
        for (int i = 0; i < maxn; i++) c[i + offset] += ret[i + offset];
        solve(0, 50000);
        for (int i = 0, x; i < q; i++) {
            scanf("%d", &x);
            printf("%lld\n", c[x + offset]);
        }
    }
}