#include <bits/stdc++.h>
using namespace std;
int T, kase = 1;

void reverse(int l, int r, vector<int> &a) {
    while (l < r) {
        swap(a[l], a[r]);
        l++, r--;
    }
}
bool work(int n, int k) {
    if (k < n - 1) return false;
    if (k > (n + 2) * (n - 1) / 2) return false;
    k -= n - 1;

    vector<int> a(n);
    iota(a.begin(), a.end(), 1);
    for (int i = n - 1; i >= 0; i--) {
        int cost = n - i - 1;
        if (k >= cost) {
            reverse(i, n - 1, a);
            k -= cost;
        } else {
            reverse(i, i + k, a);
            k = 0;
        }
    }
    cout << "Case #" << kase++ << ": ";
    for (auto &u : a) cout << u << ' ';
    cout << endl;
    return true;
}
int main() {
    cin >> T;
    while (T--) {
        int n, k;
        cin >> n >> k;
        if (!work(n, k)) cout << "Case #" << kase++ << ": IMPOSSIBLE" << endl;
    }
}
