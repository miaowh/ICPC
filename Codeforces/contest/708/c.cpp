#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int n, k;

void solve(int x, int y) {
    if (x & 1) {
        printf("%d %d %d\n", 1, x / 2, x / 2);
    } else if (x % 4 == 0) {
        printf("%d %d %d\n", x / 2, x / 4, x / 4);
    } else {
        printf("%d %d %d\n", x / 2 - 1, x / 2 - 1, 2);
    }
}
int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &k);
        for (int i = 0; i < k - 3; i++) printf("1 ");
        solve(n - k + 3, 3);
    }
}