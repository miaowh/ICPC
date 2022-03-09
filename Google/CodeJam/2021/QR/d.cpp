#include <bits/stdc++.h>
using namespace std;
int ans[100];
int T, n, q;

int ask(int s, int t, int u) {
    cout << s << ' ' << t << ' ' << u << endl;
    int ret;
    cin >> ret;
    return ret;
}

void solve(int pos, int s, int t, const vector<int> &a) {
    vector<int> less, mid, large;
    for (auto &u : a) {
        if (u == s or u == t) continue;
        int m = ask(s, t, u);
        if (m == s)
            less.push_back(u);
        else if (m == t)
            large.push_back(u);
        else
            mid.push_back(u);
    }
    ans[pos + less.size()] = s;
    ans[pos + less.size() + 1 + mid.size()] = t;

    if (!less.empty()) {
        if (less.size() == 1)
            ans[pos] = less[0];
        else {
            int x = less[0], y = less[1];
            int m = ask(x, y, s);
            if (m == x)
                solve(pos, y, x, less);
            else
                solve(pos, x, y, less);
        }
    }
    if (!mid.empty()) {
        if (mid.size() == 1)
            ans[pos + less.size() + 1] = mid[0];
        else {
            int x = mid[0], y = mid[1];
            int m = ask(x, y, t);
            if (m == x)
                solve(pos + less.size() + 1, y, x, mid);
            else
                solve(pos + less.size() + 1, x, y, mid);
        }
    }
    if (!large.empty()) {
        if (large.size() == 1)
            ans[pos + less.size() + mid.size() + 2] = large[0];
        else {
            int x = large[0], y = large[1];
            int m = ask(x, y, t);
            if (m == x)
                solve(pos + less.size() + 2 + mid.size(), x, y, large);
            else
                solve(pos + less.size() + 2 + mid.size(), y, x, large);
        }
    }
}

void work() {
    vector<int> a(n);
    iota(a.begin(), a.end(), 1);
    solve(0, 1, 2, a);
    for (int i = 0; i < n; i++) cout << ans[i] << ' ';
    cout << endl;
    int ret;
    cin >> ret;

    if (ret != 1) assert(false);
}

int main() {
    cin >> T >> n >> q;
    while (T--) work();
}