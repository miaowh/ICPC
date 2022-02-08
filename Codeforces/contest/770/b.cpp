#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 1e5 + 5;
ll a[maxn];

int main() {
    int T;
    cin >> T;
    while (T--) {
        ll n, x, y;
        cin >> n >> x >> y;
        int cnt = 0;
        string ans = "Alice";
        for (int i = 0; i < n; i++) cin >> a[i], cnt += a[i] & 1;
        if ((x & 1) ^ (y & 1) ^ (cnt & 1)) {
            ans = "Bob";
        }
        cout << ans << endl;
    }
}