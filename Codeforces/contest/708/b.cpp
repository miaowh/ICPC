#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 5;
int a[maxn], cnt[maxn];

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n, m;
        scanf("%d%d", &n, &m);

        for (int i = 0; i < n; i++) scanf("%d", a + i), a[i] %= m, cnt[a[i]]++;

        int tot = 0;
        for (int i = 0; i < m; i++) {
            if (i == 0 || i == m - i) {
                if (cnt[i]) tot++;
            } else if (cnt[i] || cnt[m - i]) {
                tot += 1 + max(0, abs(cnt[i] - cnt[m - i]) - 1);
            }

            cnt[i] = 0;
            cnt[m - i] = 0;
        }

        printf("%d\n", tot);
    }
}