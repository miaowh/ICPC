#include <bits/stdc++.h>
using namespace std;
const int maxn = 595;
int a[maxn][maxn];
int b[20];

int main() {
    int x = 720720;
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) scanf("%d", &a[i][j]);
    for (int i = 0; i <= 16; i++) b[i] = i * i * i * i;
    int res;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if ((i + j) & 1)
                res = x;
            else
                res = b[a[i][j]] + x;
            printf("%d ", res);
        }
        puts("");
    }
}