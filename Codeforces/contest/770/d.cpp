#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int ask(int a, int b, int c) {
    cout << "? " << a << ' ' << b << ' ' << c << endl;
    int ret;
    cin >> ret;
    return ret;
}
void guess(int a, int b) { cout << "! " << a << ' ' << b << endl; }

int main() {
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;

        int mx = -1, idx = -1;
        for (int i = 3; i <= n; i++) {
            int res = ask(1, 2, i);
            if (res > mx) {
                mx = res;
                idx = i;
            }
        }

        int a = idx;
        mx = -1, idx = -1;
        for (int i = 2; i <= n; i++) {
            if (i == a) continue;
            int res = ask(1, a, i);
            if (res > mx) {
                mx = res;
                idx = i;
            }
        }
        guess(a, idx);
    }
}

/*
0 2 4 6 8

2,4

*/