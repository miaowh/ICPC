#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 5e3 + 5;
int s[maxn], tag[maxn];
ll dp[maxn];

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; i++) scanf("%d", tag + i);
        for (int i = 0; i < n; i++) scanf("%d", s + i);
        for (int i = 0; i < n; i++) {
            for (int j = i - 1; j >= 0; j--) {
                if (tag[i] == tag[j]) continue;
                ll dpi = dp[i], dpj = dp[j], x = abs(s[i] - s[j]);
                dp[i] = max(dp[i], dpj + x);
                dp[j] = max(dp[j], dpi + x);
            }
        }
        printf("%lld\n", *max_element(dp, dp + n));
        for (int i = 0; i < n; i++) dp[i] = 0;
    }
}

/*
dp[i] reprensents the max points earned by ending with problem i.
*/