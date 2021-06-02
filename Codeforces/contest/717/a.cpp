#include <bits/stdc++.h>
using namespace std;
const int maxn = 105;
int a[maxn];
int n, k;

void work() {
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; i++) scanf("%d", a + i);
    for (int i = 0; i < n - 1; i++) {
        if (a[i] > k) {
            a[i] -= k;
            a[n - 1] += k;
            return;
        }
        k -= a[i];
        a[n - 1] += a[i];
        a[i] = 0;
    }
}
int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        work();
        for (int i = 0; i < n; i++) printf("%d ", a[i]);
        puts("");
    }
}