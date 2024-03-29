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
const int maxn = 1e6 + 5;
map<double, int> Hash;
map<int, double> rHash;
struct Lines {
    double l, r, h;
    int val;
    bool operator<(const Lines &A) const { return h < A.h; }
};
struct Node {
    int cnt;      //  覆盖次数
    double len1;  // 覆盖次数大于0的长度
    double len2;  // 覆盖次数大于1的长度
};
Node seg[maxn << 2];

void build(int rt, int l, int r) {
    seg[rt].cnt = seg[rt].len1 = seg[rt].len2 = 0;
    if (l == r) return;
    int mid = l + r >> 1;
    build(lson, l, mid);
    build(rson, mid + 1, r);
}
inline void pushup(int rt, int l, int r) {
    if (seg[rt].cnt > 1)
        seg[rt].len1 = seg[rt].len2 = rHash[r + 1] - rHash[l];
    else if (seg[rt].cnt == 1) {
        seg[rt].len1 = rHash[r + 1] - rHash[l];
        if (l == r)
            seg[rt].len2 = 0;
        else
            seg[rt].len2 = seg[lson].len1 + seg[rson].len1;

    } else {
        if (l == r)
            seg[rt].len1 = seg[rt].len2 = 0;
        else {
            seg[rt].len1 = seg[lson].len1 + seg[rson].len1;
            seg[rt].len2 = seg[lson].len2 + seg[rson].len2;
        }
    }
}
void update(int rt, int l, int r, int L, int R, int val) {
    if (L <= l && R >= r) {
        seg[rt].cnt += val;
        pushup(rt, l, r);
        return;
    }
    int mid = l + r >> 1;
    if (L <= mid) update(lson, l, mid, L, R, val);
    if (R >= mid + 1) update(rson, mid + 1, r, L, R, val);
    pushup(rt, l, r);
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
        int n;
        scanf("%d", &n);
        double x1, x2, y1, y2;
        vector<Lines> line;
        set<double> X;
        for (int i = 1; i <= n; i++) {
            scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
            line.push_back({x1, x2, y1, 1});
            line.push_back({x1, x2, y2, -1});
            X.insert(x1);
            X.insert(x2);
        }
        sort(line.begin(), line.end());
        int cnt = 0;
        Hash.clear();
        rHash.clear();
        for (auto &v : X) Hash[v] = ++cnt, rHash[cnt] = v;
        build(1, 1, cnt);
        double area = 0;
        for (int i = 0; i < line.size() - 1; i++) {
            update(1, 1, cnt, Hash[line[i].l], Hash[line[i].r] - 1,
                   line[i].val);
            area += seg[1].len2 * (line[i + 1].h - line[i].h);
        }
        printf("%.2lf\n", area);
    }
}