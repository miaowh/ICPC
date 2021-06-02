#include <bits/stdc++.h>
using namespace std;
const int maxn = 105;
int a[maxn], cnt[maxn];
int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        memset(cnt, 0, sizeof(cnt));
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; i++) scanf("%d", a + i), cnt[a[i]]++;
        vector<int> x, y;
        for (int i = 0; i < maxn; i++) {
            if (cnt[i] > 0) {
                cnt[i]--;
                x.push_back(i);
                while (cnt[i] > 0) {
                    y.push_back(i);
                    cnt[i]--;
                }
            }
        }
        for (auto &u : x) printf("%d ", u);
        for (auto &u : y) printf("%d ", u);
        puts("");
    }
}