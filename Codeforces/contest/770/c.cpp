#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int T;
    cin >> T;
    while (T--) {
        int n, k;
        cin >> n >> k;
        if (k > 1 and (n & 1 or n * k % 2)) {
            cout << "NO" << endl;
        } else {
            cout << "YES" << endl;
            vector<int> res;
            for (int i = 1; i <= n * k; i += 2) res.push_back(i);
            for (int i = 2; i <= n * k; i += 2) res.push_back(i);
            for (int i = 0; i < res.size(); i++) {
                cout << res[i] << ' ';
                if (i % k == k - 1) cout << endl;
            }
        }
    }
}
