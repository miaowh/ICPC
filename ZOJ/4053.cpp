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
const int maxn = 1e5 + 5;
ll a[maxn], p[maxn], pre[maxn];

struct SEG {
    int l, r;
    ll cnt;
    bool operator<(const SEG &A) const { return r < A.r; }
};

set<SEG> seg;
multiset<ll> val;
ll sum[maxn * 30];
int root[maxn * 30];
int lch[maxn * 30], rch[maxn * 30];
int n, dfn, tot;
inline void pushup(int k) { sum[k] = sum[lch[k]] + sum[rch[k]]; }
void build(int &k, int l, int r) {
    k = ++dfn;
    if (l == r) {
        sum[k] = 0;
        return;
    }
    int mid = l + r >> 1;
    build(lch[k], l, mid);
    build(rch[k], mid + 1, r);
    pushup(k);
}
inline void newnode(int old, int k) {
    lch[k] = lch[old];
    rch[k] = rch[old];
    sum[k] = sum[old];
}
void update(int old, int &k, int l, int r, int p, int x) {
    k = ++dfn;
    newnode(old, k);
    if (l == r) {
        sum[k] += x;
        return;
    }
    int mid = l + r >> 1;
    if (p <= mid) update(lch[old], lch[k], l, mid, p, x);
    if (p >= mid + 1) update(rch[old], rch[k], mid + 1, r, p, x);
    pushup(k);
}
ll query(int k, int l, int r, int L, int R) {
    if (L > R) return 0;
    if (L <= l && R >= r) return sum[k];
    int mid = l + r >> 1;
    ll ret = 0;
    if (L <= mid) ret += query(lch[k], l, mid, L, R);
    if (R >= mid + 1) ret += query(rch[k], mid + 1, r, L, R);
    return ret;
}

void work(int l, int k, int r, ll fa_cnt) {
    if (l == r)
        return;
    else if (r - l == 1) {
        val.insert(0);
        if (l == k) {
            seg.insert({k + 1, r, 0});
            val.insert(0);
        } else {
            seg.insert({l, k - 1, 0});
            val.insert(0);
        }
    } else {
        if (l == k) {
            ll cnt = fa_cnt;
            cnt -= query(root[r], 1, n, 1, a[l] - 1) -
                   query(root[l - 1], 1, n, 1, a[l] - 1);
            seg.insert({l + 1, r, cnt});
            val.insert(cnt);
        } else if (r == k) {
            ll cnt = fa_cnt;
            cnt -= query(root[r], 1, n, a[r] + 1, n) -
                   query(root[l - 1], 1, n, a[r] + 1, n);
            seg.insert({l, r - 1, cnt});
            val.insert(cnt);
        } else {
            if (k - l < r - k) {
                ll cnt = pre[k - 1] - pre[l - 1];
                for (int i = l; i < k; i++) {
                    cnt -= query(root[l - 1], 1, n, a[i] + 1, n);
                }
                seg.insert({l, k - 1, cnt});
                val.insert(cnt);
                // ---
                cnt = fa_cnt - cnt;
                for (int i = l; i <= k; i++) {
                    cnt -= query(root[r], 1, n, 1, a[i] - 1);
                    cnt += query(root[k - 1], 1, n, 1, a[i] - 1);
                }
                seg.insert({k + 1, r, cnt});
                val.insert(cnt);
            } else {
                ll cnt = pre[r] - pre[k];
                for (int i = k + 1; i <= r; i++) {
                    cnt -= query(root[k], 1, n, a[i] + 1, n);
                }
                seg.insert({k + 1, r, cnt});
                val.insert(cnt);
                // ---
                cnt = fa_cnt - cnt;
                for (int i = k; i <= r; i++) {
                    cnt -= query(root[k], 1, n, a[i] + 1, n);
                    cnt += query(root[l - 1], 1, n, a[i] + 1, n);
                }
                seg.insert({l, k - 1, cnt});
                val.insert(cnt);
            }
        }
    }
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
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) scanf("%lld", a + i);
        for (int i = 1; i <= n; i++) scanf("%lld", p + i);
        ll cnt = 0;
        val.clear();
        seg.clear();
        //----
        dfn = 0;
        build(root[0], 1, n);
        for (int i = 1; i <= n; i++) {
            update(root[i - 1], root[i], 1, n, a[i], 1);
            pre[i] = pre[i - 1] + query(root[i], 1, n, a[i] + 1, n);
        }
        seg.insert({1, n, pre[n]});
        val.insert(pre[n]);
        //---
        vector<ll> ans;
        ans.pb(pre[n]);
        for (int i = 1; i < n; i++) {
            ll k = p[i] ^ (ans.back());
            auto it = seg.lower_bound({0, k, 0});
            val.erase(val.find(it->cnt));
            seg.erase(it);
            int l = it->l;
            int r = it->r;
            work(l, k, r, it->cnt);
            ans.push_back(*(val.rbegin()));
        }
        for (int i = 0; i < ans.size(); i++) {
            if (i)
                printf(" %lld", ans[i]);
            else
                printf("%lld", ans[i]);
        }
        puts("");
    }
}