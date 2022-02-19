#include <bits/stdc++.h>
using namespace std;

int main() {
    int m, n;
    cin >> m;
    map<int, bool> vis;
    vector<int> a, b;
    vector<vector<char>> ans(m);
    for (int k = 0; k < m; k++) {
        cin >> n;
        for (int i = 0, u; i < n; i++) {
            cin >> u;
            if (vis[u] == 0)
                a.push_back(u), ans[k].push_back('L');
            else
                b.push_back(u), ans[k].push_back('R');
            vis[u] ^= 1;
        }
    }
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    if (a == b) {
        puts("YES");
        for (auto &vec : ans) {
            for (auto &c : vec) cout << c;
            cout << endl;
        }
    } else
        puts("NO");
}

/*
1, 1, 1, 2
3, 3, 3, 4
1, 3


1, 1, 3, 2
1, 1
3, 2

average in overall
average in local

dinic?
*/