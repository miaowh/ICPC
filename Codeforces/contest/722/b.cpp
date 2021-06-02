#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 5;
int a[maxn];

int work() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", a + i);
    }
    sort(a, a + n);
    int tmp = 2e9 + 5;
    for (int i = 1; i < n; i++) {
        int x = a[i] - a[i - 1];
        if (x >= 0) {
            tmp = min(x, tmp);
            if (tmp < a[i]) return i;

        } else
            tmp = min(tmp, abs(x));
    }
    return n;
}
int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        printf("%d\n", work());
    }
}