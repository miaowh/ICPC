#include <bits/stdc++.h>
using namespace std;
using ll = long long;
void task1(int n) {
    if (n == 1) {
        puts("2 1");
        return;
    }
    if (n & 1)
        puts("0");
    else {
        printf("2");
        for (int i = 0; i < n; i++) {
            if (i & 1)
                printf(" %d", i);
            else
                printf(" %d", n - i);
        }
        puts("");
    }
}

int Pow(int a, int b, int mod) {
    int ret = 1;
    while (b) {
        if (b & 1) ret = 1LL * ret * a % mod;
        a = 1LL * a * a % mod;
        b >>= 1;
    }
    return ret;
}
void task2(int n) {
    if (n == 1) {
        puts("2 1");
        return;
    }
    if (n == 4) {
        puts("2 1 3 2 4");
        return;
    }
    for (int i = 2; 1LL * i * i <= n; i++) {
        if (n % i == 0) {
            puts("0");
            return;
        }
    }
    printf("2 1");
    for (int i = 2; i < n; i++)
        printf(" %d", 1LL * i * Pow(i - 1, n - 2, n) % n);
    printf(" %d\n", n);
}
int main() {
    int X, T;
    scanf("%d%d", &X, &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        if (X == 1)
            task1(n);
        else
            task2(n);
    }
}