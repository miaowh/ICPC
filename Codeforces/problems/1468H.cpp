#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 5;
int b[maxn];
bool vis[maxn];

void work() {
    int n, k, m;
    scanf("%d%d%d", &n, &k, &m);
    for (int i = 1; i <= n; i++) vis[i] = 0;
    for (int i = 0; i < m; i++) scanf("%d", b + i), vis[b[i]] = 1;

    if ((n - m) % (k - 1)) {
        puts("NO");
        return;
    }
    int cnt = (k - 1) / 2;
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        if (vis[i] == 0)
            sum++;
        else {
            if (sum >= cnt && (n - m) - sum >= cnt) {
                puts("YES");
                return;
            }
        }
    }
    puts("NO");
}
int main() {
    int T;
    scanf("%d", &T);
    while (T--) work();
}