#include <bits/stdc++.h>
using namespace std;

bool work(string s) {
    int cnt = 0;
    for (auto &c : s) {
        if (c == 'T') cnt++;
        if (c == 'M') cnt--;
        if (cnt < 0) return false;
    }
    return cnt == s.size() / 3;
}
int main() {
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        string s;
        cin >> s;
        string rs = s;
        reverse(rs.begin(), rs.end());
        if (work(s) && work(rs))
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
}