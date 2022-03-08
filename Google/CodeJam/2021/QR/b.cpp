#include <bits/stdc++.h>
using namespace std;
const int maxn = 105;

int cal(int x, int y, string s) {
    int ret = 0;
    for (int i = 0; i < s.size() - 1; i++) {
        if (s[i] == s[i + 1]) continue;
        if (s[i] == 'C')
            ret += x;
        else
            ret += y;
    }
    return ret;
}

int work(int x, int y, string s) {
    int ret = 0x3f3f3f3f;
    string tmp = s;
    for (auto &c : tmp)
        if (c == '?') c = 'C';
    ret = min(ret, cal(x, y, tmp));
    tmp = s;
    for (auto &c : tmp)
        if (c == '?') c = 'J';
    ret = min(ret, cal(x, y, tmp));

    bool cnt = false;
    tmp = s;
    for (auto &c : tmp)
        if (c == '?') {
            if (cnt)
                c = 'C';
            else
                c = 'J';
            cnt ^= 1;
        }
    ret = min(ret, cal(x, y, tmp));

    cnt = true;
    tmp = s;
    for (auto &c : tmp)
        if (c == '?') {
            if (cnt)
                c = 'C';
            else
                c = 'J';
            cnt ^= 1;
        }
    ret = min(ret, cal(x, y, tmp));

    return ret;
}

int main() {
    int T, kase = 1;
    cin >> T;
    while (T--) {
        int ans = 0;
        int x, y;
        string s;
        cin >> x >> y >> s;

        string tmp;
        int i = 0;
        while (i < s.size()) {
            if (s[i] == '?')
                tmp.push_back(s[i]);
            else {
                if (tmp.empty())
                    tmp.push_back(s[i]);
                else {
                    tmp.push_back(s[i]);
                    ans += work(x, y, tmp);
                    tmp = s[i];
                }
            }
            i++;
        }
        ans += work(x, y, tmp);
        cout << "Case #" << kase++ << ": " << ans << endl;
    }
}
