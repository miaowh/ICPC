#include <bits/stdc++.h>
using namespace std;
const int maxn = 3e5 + 5;
const int ninf = 0xc0c0c0c0;
using ll = long long;

int a[maxn];
int n, q;

inline int get(int i) {
    if (i == 0 || i == n + 1) return 0;
    if (a[i] > a[i - 1] && a[i] > a[i + 1])
        return a[i];
    else if (a[i] < a[i - 1] && a[i] < a[i + 1])
        return -a[i];
    return 0;
}
int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &q);
        for (int i = 1; i <= n; i++) scanf("%d", a + i);
        a[0] = a[n + 1] = ninf;
        ll sum = 0;
        for (int i = 1; i <= n; i++) sum += get(i);
        printf("%lld\n", sum);

        for (int i = 0, l, r; i < q; i++) {
            scanf("%d%d", &l, &r);
            set<int> pos;
            for (int j = -1; j <= 1; j++) pos.insert(l + j), pos.insert(r + j);
            for (auto &x : pos) sum -= get(x);
            swap(a[l], a[r]);
            for (auto &x : pos) sum += get(x);

            printf("%lld\n", sum);
        }
    }
}