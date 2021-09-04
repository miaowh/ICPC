#include <bits/stdc++.h>
using namespace std;

int main() {
    cout << -3 / 2 << endl;
    int T;
    cin >> T;
    while (T--) {
        int a, b;
        cin >> a >> b;
        if (a < b / 2 + 1) a = b / 2 + 1;
        cout << b % a << endl;
    }
}