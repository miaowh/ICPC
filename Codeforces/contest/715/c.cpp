#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 2e3 + 5;
ll dp[maxn][maxn];

int main() {
    int n;
    cin >> n;
    vector<int> s(n);
    for (int i = 0; i < n; i++) cin >> s[i];
    sort(s.begin(), s.end());

    for (int i = 0; i < n; i++) dp[i][i] = 0;

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < n - i; j++) {
            dp[j][j + i] =
                s[j + i] - s[j] + min(dp[j + 1][j + i], dp[j][j + i - 1]);
        }
    }

    cout << dp[0][n - 1] << endl;
}