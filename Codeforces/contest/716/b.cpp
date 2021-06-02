#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7;

int Pow(int a, int b) {
    int ret = 1;
    while (b) {
        if (b & 1) ret = (long long)a * ret % mod;
        a = (long long)a * a % mod;
        b >>= 1;
    }
    return ret;
}
int main() {
    int T;
    cin >> T;
    while (T--) {
        int n, k;
        cin >> n >> k;
        cout << Pow(n, k) << endl;
    }
}