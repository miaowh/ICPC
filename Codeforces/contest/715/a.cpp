#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e3 + 5;

int main() {
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<int> a[2];
        for (int i = 0, u; i < n; i++) {
            cin >> u;
            a[u & 1].push_back(u);
        }
        for (int i = 0; i < 2; i++)
            for (auto &u : a[i]) cout << u << ' ';
        cout << endl;
    }
}