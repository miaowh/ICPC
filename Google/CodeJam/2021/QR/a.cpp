#include <bits/stdc++.h>
using namespace std;
const int maxn = 105;
int a[maxn];

int main() {
    int T, kase = 1;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) cin >> a[i];
        int ans = 0;

        for (int i = 0; i < n - 1; i++) {
            int k = i;
            for (int j = i; j < n; j++)
                if (a[k] > a[j]) k = j;
            ans += k - i + 1;
            for (int j = i, t = k; j < t; j++, t--) swap(a[j], a[t]);
        }

        cout << "Case #" << kase++ << ": " << ans << endl;
    }
}