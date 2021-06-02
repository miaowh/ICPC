#include <bits/stdc++.h>
using namespace std;
int n;
string bs[3];

bool work(int a, int b, char c) {
    string s;
    int N = 2 * n;
    int i = 0, j = 0;
    while (i < N && j < N) {
        while (i < N && bs[a][i] != c) s.push_back(bs[a][i++]);
        while (j < N && bs[b][j] != c) s.push_back(bs[b][j++]);
        s.push_back(c);
        i++, j++;
    }
    while (i < N) s.push_back(bs[a][i++]);
    while (j < N) s.push_back(bs[b][j++]);

    if (s.size() <= 3 * n) {
        cout << s << endl;
        return true;
    }
    return false;
}
void solve() {
    cin >> n;
    for (int i = 0; i < 3; i++) cin >> bs[i];
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i == j) continue;
            if (work(i, j, '0')) return;
            if (work(i, j, '1')) return;
        }
    }
}
int main() {
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
}
