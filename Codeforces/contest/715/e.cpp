#include <bits/stdc++.h>
using namespace std;
using ll = long long;
ll a[100];

bool solve() {
    int n;
    ll k;
    scanf("%d%lld", &n, &k);
    int base = 1;
    vector<int> ans;
    k--;
    for (int i = n; i > 0;) {
        if (i >= 64) {
            ans.push_back(base++);
            i--;
        } else {
            int x = -1;
            for (int j = 1; j <= i; j++) {
                if (k >= a[i - j]) {
                    k -= a[i - j];
                } else {
                    x = j - 1;
                    break;
                }
            }
            if (x == -1) return false;

            for (int j = x; j >= 0; j--) ans.push_back(base + j);
            base += x + 1;
            i -= x + 1;
        }
    }

    for (auto &x : ans) printf("%d ", x);
    puts("");
    return true;
}
int main() {
    a[0] = a[1] = 1;
    for (int i = 2; i < 64; i++) a[i] = a[i - 1] * 2;
    int T;
    scanf("%d", &T);
    while (T--) {
        if (solve() == false) puts("-1");
    }
}
