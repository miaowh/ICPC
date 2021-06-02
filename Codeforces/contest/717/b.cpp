#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e3 + 5;
int a[maxn];

void work() {
    int n;
    cin >> n;
    int xsum = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", a + i);
        xsum ^= a[i];
    }
    if (xsum == 0) {
        puts("YES");
        return;
    }
    int cnt = 0, val = 0;
    for (int i = 0; i < n; i++) {
        val ^= a[i];
        if (val == xsum) {
            val = 0;
            cnt++;
        }
    }
    if (cnt > 1)
        puts("YES");
    else
        puts("NO");
}
int main() {
    int T;
    cin >> T;
    while (T--) {
        work();
    }
}