#include <bits/stdc++.h>
using namespace std;

void work(int n, string s) {
    int p = n / 2;
    for (int i = p; i < n; i++) {
        if (s[i] == '0') {
            cout << 1 << ' ' << i + 1 << ' ' << 1 << ' ' << i << endl;
            return;
        }
    }
    for (int i = 0; i < p; i++) {
        if (s[i] == '0') {
            cout << i + 1 << ' ' << n << ' ' << i + 2 << ' ' << n << endl;
            return;
        }
    }
    cout << 1 << ' ' << n - 1 << ' ' << 2 << ' ' << n << endl;
}
int main() {
    int T;
    cin >> T;
    while (T--) {
        int n;
        string s;
        cin >> n >> s;
        work(n, s);
    }
}