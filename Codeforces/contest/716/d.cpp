#include <bits/stdc++.h>
using namespace std;
const int maxn = 3e5 + 5;
int a[maxn], ans[maxn];

struct Query {
    int l, r, id;
} Q[maxn];
int S;
bool cmp(const Query& A, const Query& B) {
    if (A.l / S == B.l / S) return A.r < B.r;
    return A.l < B.l;
}
int num[maxn], cnt[maxn];
int mx;
void pls(int x) {
    cnt[num[a[x]]]--;
    num[a[x]]++;
    cnt[num[a[x]]]++;
    if (num[a[x]] > mx) mx = num[a[x]];
}
void sbs(int x) {
    cnt[num[a[x]]]--;
    num[a[x]]--;
    cnt[num[a[x]]]++;
    if (cnt[mx] == 0) mx--;
}

int main() {
    int n, q;
    scanf("%d%d", &n, &q);
    S = sqrt(n);
    for (int i = 0; i < n; i++) scanf("%d", a + i);
    for (int i = 0; i < q; i++) {
        scanf("%d%d", &Q[i].l, &Q[i].r);
        Q[i].l--;
        Q[i].id = i;
    }
    sort(Q, Q + q, cmp);
    int l = 0, r = 0;
    mx = 0;
    for (int i = 0; i < q; i++) {
        while (r < Q[i].r) pls(r++);
        while (l > Q[i].l) pls(--l);
        while (r > Q[i].r) sbs(--r);
        while (l < Q[i].l) sbs(l++);

        int len = Q[i].r - Q[i].l, res;
        if (mx <= (len + 1) / 2)
            res = 1;
        else
            res = mx - (len - mx + 1) + 1;
        ans[Q[i].id] = res;
    }
    for (int i = 0; i < q; i++) printf("%d\n", ans[i]);
}