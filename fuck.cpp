#include <bits/stdc++.h>
using namespace std;
const int maxn = 1005;
int a[maxn][maxn];
int rowSum[maxn], colSum[maxn];

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &a[i][j]);
            rowSum[i] += a[i][j];
            colSum[j] += a[i][j];
        }
    }
    int ans = 0;

    for (int i = 0; i < n; i++) {
        int le = 0, ri = rowSum[i];
        for (int j = 0; j < m; j++) {
            if (a[i][j])
                le++, ri--;
            else
                ans += (le > 0) + (ri > 0);
        }
    }

    for (int j = 0; j < m; j++) {
        int up = 0, down = colSum[j];
        for (int i = 0; i < n; i++) {
            if (a[i][j])
                up++, down--;
            else
                ans += (up > 0) + (down > 0);
        }
    }
    printf("%d\n", ans);
}