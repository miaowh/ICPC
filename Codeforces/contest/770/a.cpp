#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int T;
    cin >> T;
    while (T--) {
        int n, k;
        cin >> n >> k;
        string s;
        cin >> s;
        int ans = 1;
        for (int i = 0, j = s.size() - 1;; i++, j--) {
            if (i > j) break;
            if (s[i] != s[j]) {
                ans = 2;
            }
        }
        if (!k) ans = 1;
        cout << ans << endl;
    }
}