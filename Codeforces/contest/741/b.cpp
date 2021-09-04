#include <bits/stdc++.h>
using namespace std;

bool isprime(int x) {
    if (x == 1) return false;
    for (int i = 2; i * i <= x; i++)
        if (x % i == 0) return false;
    return true;
}
void work(int n, string s) {
    for (int i = 0; i < n; i++) {
        int num = s[i] - '0';
        if (!isprime(num)) {
            cout << 1 << '\n' << num << endl;
            return;
        }
    }
    for (int i = 0; i < n; i++) {
        int a = s[i] - '0';
        for (int j = i + 1; j < n; j++) {
            int num = a * 10 + s[j] - '0';
            if (!isprime(num)) {
                cout << 2 << '\n' << num << endl;
                return;
            }
        }
    }
}
int main() {
    int T;
    cin >> T;
    while (T--) {
        int n;
        string s;
        cin >> n >> s;
        work(n, s);
    }
}