#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, q;
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            long long x = 0;
            if (i & 1) x = 1LL << (i + j);
            cout << x << ' ';
        }
        cout << endl;
    }
    cin >> q;
    for (int i = 0; i < q; i++) {
        long long k;
        cin >> k;
        int x = 0, y = 0;
        cout << x + 1 << ' ' << y + 1 << endl;
        while (!(x == n - 1 && y == n - 1)) {
            if (x & 1) {
                if (k & (1LL << (x + 1 + y)))
                    y++;
                else
                    x++;
            } else {
                if (k & (1LL << (x + 1 + y)))
                    x++;
                else
                    y++;
            }
            cout << x + 1 << ' ' << y + 1 << endl;
        }
    }
}

/*
题意：构造一个矩阵使得从左上角到右下角，所有路径的权值都不同。
 */