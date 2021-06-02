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
const int mod = 1e9 + 7;
int a[maxn];
int n, m, seed, vmax;
ll Pow(ll a, ll b, int p) {
    ll ret = 1;
    a %= p;  // !!!
    while (b) {
        if (b & 1) ret = ret * a % p;
        a = a * a % p;
        b >>= 1;
    }
    return ret;
}
inline int rnd() {
    ll ret = seed;
    seed = ((seed * 7LL) + 13) % mod;
    return ret;
}
struct Node {
    int l, r;
    mutable ll val;
    Node(int l = 0, int r = 0, ll val = 0) : l(l), r(r), val(val) {}
    bool operator<(const Node& A) const { return l < A.l; }
};
set<Node> odt;

set<Node>::iterator split(int pos) {
    auto it = odt.lower_bound(Node(pos));
    if (it != odt.end() && it->l == pos) return it;
    --it;
    int L = it->l, R = it->r;
    ll v = it->val;
    odt.erase(it);
    odt.insert(Node(L, pos - 1, v));
    return odt.insert(Node(pos, R, v)).first;
}

void assign(int l, int r, int val) {
    auto itl = split(l), itr = split(r + 1);
    odt.erase(itl, itr);
    odt.insert(Node(l, r, val));
}

void add(int l, int r, int val) {
    auto itl = split(l), itr = split(r + 1);
    for (; itl != itr; itl++) itl->val += val;
}
ll Rank(int l, int r, int k) {
    vector<pair<ll, int>> vp;
    auto itl = split(l), itr = split(r + 1);
    vp.clear();
    for (; itl != itr; itl++) vp.push_back(mp(itl->val, itl->r - itl->l + 1));
    sort(vp.begin(), vp.end());
    for (auto& it : vp) {
        k -= it.second;
        if (k <= 0) return it.first;
    }
}
ll sum(int l, int r, int x, int p) {
    auto itl = split(l), itr = split(r + 1);
    ll ret = 0;
    for (; itl != itr; itl++)
        ret = (ret + 1LL * (itl->r - itl->l + 1) * Pow(itl->val, x, p) % p) % p;
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
    scanf("%d%d%d%d", &n, &m, &seed, &vmax);
    for (int i = 1; i <= n; i++) {
        a[i] = (rnd() % vmax) + 1;
        odt.insert(Node(i, i, a[i]));
    }
    odt.insert(Node(n + 1, n + 1, 0));
    for (int i = 1, op, l, r, x, y; i <= m; i++) {
        op = (rnd() % 4) + 1;
        l = (rnd() % n) + 1;
        r = (rnd() % n) + 1;
        if (l > r) swap(l, r);
        if (op == 3)
            x = (rnd() % (r - l + 1)) + 1;
        else
            x = (rnd() % vmax) + 1;
        if (op == 4) y = (rnd() % vmax) + 1;
        // ---
        if (op == 1)
            add(l, r, x);
        else if (op == 2)
            assign(l, r, x);
        else if (op == 3)
            printf("%lld\n", Rank(l, r, x));
        else
            printf("%lld\n", sum(l, r, x, y));
    }
}