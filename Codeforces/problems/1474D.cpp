#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 5;
const int inf = 0x3f3f3f3f;
using ll = long long;
int a[maxn];
ll pre[maxn], suf[maxn];

bool work(int n) {
    pre[0] = 0;
    for (int i = 1; i <= n; i++) {
        if (pre[i - 1] < 0 or a[i - 1] < pre[i - 1])
            pre[i] = -inf;
        else
            pre[i] = a[i - 1] - pre[i - 1];
    }
    suf[n - 1] = 0;
    for (int i = n - 2; i >= 0; i--) {
        if (suf[i + 1] < 0 or a[i + 1] < suf[i + 1])
            suf[i] = -inf;
        else
            suf[i] = a[i + 1] - suf[i + 1];
    }
    if (pre[n] == 0) return true;

    for (int i = 0; i < n - 1; i++) {
        if (pre[i] < 0 or suf[i + 1] < 0) continue;
        if (a[i + 1] < pre[i] or a[i] < suf[i + 1]) continue;
        if (pre[i] + a[i] == a[i + 1] + suf[i + 1]) return true;
    }
    return false;
}
int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; i++) scanf("%d", a + i);
        printf("%s\n", work(n) ? "YES" : "NO");
    }
}