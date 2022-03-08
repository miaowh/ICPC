#include <bits/stdc++.h>
using namespace std;
const int maxn = 3e5 + 5;
int a[maxn], b[maxn], f[maxn];

int main() {
    int n, q, mod;
    scanf("%d%d%d", &n, &q, &mod);
    for (int i = 0; i < n; i++) scanf("%d", a + i);
    for (int i = 0, u; i < n; i++) {
        scanf("%d", &u);
        a[i] -= u;
        while (a[i] < 0) a[i] += mod;
        a[i] %= mod;
    }
    f[0] = 1, f[1] = 1;
    for (int i = 2; i < n; i++) f[i] = (f[i - 1] + f[i - 2]) % mod;
    int zeros = 0;
    for (int i = 0; i < n; i++) {
        b[i] = a[i];
        if (i > 0) b[i] -= a[i - 1];
        if (i > 1) b[i] -= a[i - 2];
        while (b[i] < 0) b[i] += mod;
        b[i] %= mod;
        if (!b[i]) zeros++;
    }

    char op[2];
    for (int i = 0, l, r; i < q; i++) {
        scanf("%s%d%d", op, &l, &r);
        l--, r--;
        vector<int> idx = {l, r + 1, r + 2};
        vector<int> val = {1, -f[r - l + 1], -f[r - l]};
        int sign = op[0] == 'A' ? 1 : -1;

        for (int j = 0; j < 3; j++) {
            int p = idx[j], v = val[j];
            if (p >= n) continue;
            if (!b[p]) zeros--;
            b[p] += v * sign;
            while (b[p] < 0) b[p] += mod;
            b[p] %= mod;
            if (!b[p]) zeros++;
        }

        if (zeros == n)
            puts("YES");
        else
            puts("NO");
    }
}
/*
c[i] = a[i] - b[i]
d[i] = c[i] - c[i-1] - c[i-2]

*/