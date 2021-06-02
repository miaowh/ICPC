#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 5;
const int N = 1e6 + 5;

int a[maxn];
int n;

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d", a + i);
    sort(a, a + n);

    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (i && a[i] == a[i - 1]) continue;
        for (int j = 1; j * a[i] < N + a[i]; j++) {
            int t = lower_bound(a + i, a + n, (j + 1) * a[i]) - a - 1;
            ans = max(ans, a[t] % a[i]);
            if (t == n - 1) break;
        }
    }
    printf("%d\n", ans);
}