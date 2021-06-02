#include <bits/stdc++.h>
using namespace std;
const int maxn = 5e5 + 5;
int a[maxn], b[maxn];

int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    a[0] = -2e9, a[n + 1] = 2e9;
    for (int i = 1; i <= n; i++) scanf("%d", a + i), a[i] -= i;
    for (int i = 1; i <= k; i++) scanf("%d", b + i);
    b[0] = 0, b[k + 1] = n + 1;
    int ans = 0;
    for (int i = 1; i <= k + 1; i++) {
        int le = b[i - 1], ri = b[i];
        if (a[le] > a[ri]) {
            puts("-1");
            return 0;
        }
        vector<int> tmp;
        for (int j = le + 1; j < ri; j++) {
            if (a[le] <= a[j] && a[j] <= a[ri]) {
                auto it = upper_bound(tmp.begin(), tmp.end(), a[j]);
                if (it == tmp.end())
                    tmp.push_back(a[j]);
                else
                    *it = a[j];
            }
        }
        ans += ri - le - 1 - tmp.size();
    }
    printf("%d\n", ans);
}
/*
minimum steps to make array increasing.

There is one condition needs to be met: a[i] - a[j] >= i - j. (i > j)
it can be turned to: a[i] - i >= a[j] - j.

let b[i] = a[i] - i, then find LIS, and subtract it from array's length.
*/