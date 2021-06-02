#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        bool flag = false;
        for (int i = 0, x; i < n; i++) {
            cin >> x;
            int y = sqrt(x);
            if (x != y * y) flag = true;
        }
        if (flag)
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
}