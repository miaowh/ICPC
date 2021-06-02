// ybmj
// #include <bits/stdc++.h>
#include <cmath>
#include <cstdio>
#include <iostream>
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
int n, m, Q;
const int maxn = 1e5 + 5;
int seg[maxn << 2], lazy[maxn << 2];

void pushup(int rt) { seg[rt] = seg[lson] | seg[rson]; }
void pushdown(int rt) {
    if (lazy[rt] == -1) return;
    seg[lson] = seg[rson] = lazy[rson] = lazy[lson] = lazy[rt];

    lazy[rt] = -1;
}
void build(int rt, int l, int r) {
    lazy[rt] = -1;
    if (l == r) {
        seg[rt] = 1;
        return;
    }
    int mid = l + r >> 1;
    build(lson, l, mid);
    build(rson, mid + 1, r);
    pushup(rt);
}

void update(int rt, int l, int r, int L, int R, int c) {
    if (l >= L && r <= R) {
        lazy[rt] = seg[rt] = 1 << (c - 1);
        return;
    }
    pushdown(rt);
    int mid = l + r >> 1;
    if (mid >= L) update(lson, l, mid, L, R, c);
    if (mid + 1 <= R) update(rson, mid + 1, r, L, R, c);
    pushup(rt);
}
int query(int rt, int l, int r, int L, int R) {
    if (l >= L && r <= R) {
        return seg[rt];
    }
    pushdown(rt);
    int ret = 0;
    int mid = l + r >> 1;
    if (mid >= L) ret |= query(lson, l, mid, L, R);
    if (mid + 1 <= R) ret |= query(rson, mid + 1, r, L, R);
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
    scanf("%d%d%d", &n, &m, &Q);
    char op[2];
    build(1, 1, n);
    for (int i = 0, x, y, z; i < Q; i++) {
        scanf("%s", op);
        if (op[0] == 'C') {
            scanf("%d%d%d", &x, &y, &z);
            if (x > y) swap(x, y);
            update(1, 1, n, x, y, z);
        } else {
            scanf("%d%d", &x, &y);
            if (x > y) swap(x, y);
            int tmp = query(1, 1, n, x, y);
            int cnt = 0;
            for (int i = 0; i < 31; i++) {
                if (tmp & (1 << i)) cnt++;
            }
            printf("%d\n", cnt);
        }
    }
}