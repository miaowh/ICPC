#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 5;
vector<int> mods[maxn];

int main() {
    int n;
    cin >> n;
    vector<int> ans;
    int tot = 1;
    for (int i = 1; i < n; i++) {
        if (__gcd(i, n) == 1) {
            ans.push_back(i);
            tot = (long long)tot * i % n;
        }
    }
    if (tot == 1) tot = -1;
    if (tot == -1)
        cout << ans.size() << endl;
    else
        cout << ans.size() - 1 << endl;
    for (auto u : ans)
        if (u != tot) cout << u << ' ';
    cout << endl;
}
