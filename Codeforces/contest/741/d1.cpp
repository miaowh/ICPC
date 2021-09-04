#include <bits/stdc++.h>
using namespace std;
const int maxn = 3e5 + 5;
char s[maxn];
int suf[maxn][2];

inline int cal(int i) {
    if (s[i] == '+')
        return 1;
    else
        return -1;
}
int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n, q;
        scanf("%d%d%s", &n, &q, s);
        suf[n][0] = suf[n][1] = 0;
        for (int i = n - 1; i >= 0; i--) {
            suf[i][0] = cal(i) + suf[i + 1][1];
            suf[i][1] = -cal(i) + suf[i + 1][0];
        }
        for (int i = 0, l, r; i < q; i++) {
            scanf("%d%d", &l, &r);
            --l, --r;
            int x = suf[l][0] - suf[r + 1][(r + 1 - l) % 2];
            int ans = 2;
            if (x == 0)
                ans = 0;
            else if (x & 1)
                ans = 1;
            printf("%d\n", ans);
        }
    }
}