#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<int> cnt(105);
        for (int i = 0, x; i < n; i++) {
            scanf("%d", &x);
            cnt[x]++;
        }
        for (int i = 0; i < 105; i++) {
            if (cnt[i]) {
                cout << n - cnt[i] << endl;
                break;
            }
        }
    }
}