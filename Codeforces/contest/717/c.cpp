#include <bits/stdc++.h>
using namespace std;
const int maxn = 105;
int a[maxn];
int vis[200005];

bool check(int n, int sum) {
    vis[0] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = sum - a[i]; j >= 0; j--) {
            if (vis[j]) vis[j + a[i]] = 1;
        }
    }
    return vis[sum / 2];
}
void work() {
    int n;
    scanf("%d", &n);
    int sum = 0;
    for (int i = 0; i < n; i++) scanf("%d", a + i), sum += a[i];
    if (sum & 1) {
        puts("0");
        return;
    }
    if (check(n, sum) == false) {
        puts("0");
        return;
    }
    for (;;) {
        for (int i = 0; i < n; i++) {
            if (a[i] & 1) {
                printf("1\n%d\n", i + 1);
                return;
            }
        }
        for (int i = 0; i < n; i++) a[i] >>= 1;
    }
}
int main() { work(); }