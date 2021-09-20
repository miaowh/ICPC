#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;
const int maxn = 2e5 + 5;
int n;
int a[maxn], b[maxn];
bool notPrime[maxn];

void calPrime() {
    notPrime[1] = true;
    for (int i = 2; i < maxn; i++)
        if (!notPrime[i])
            for (int j = 2; i * j < maxn; j++) notPrime[i * j] = true;
}
ll breakDown(ll x) {
    for (ll i = 2; i * i <= x; i++) {
        if (x % i == 0) {
            if (i != x / i && !notPrime[i] && !notPrime[x / i]) {
                return i;
            }
        }
    }
    return -1;
}

void work(int pos, ll x) {
    ll res;
    for (int i = 1; i <= n; i++) {
        if (i == pos) continue;
        cout << "? " << pos << " " << i << endl;
        cin >> res;
        if (res % x != 0) x = n / x;
        b[i] = res / x;
    }
    b[pos] = x;
}

void solve() {
    for (int i = 1; i <= n; i++) a[i - 1] = i;
    random_device rd;
    mt19937 g(rd());
    shuffle(a, a + n, g);

    for (ll i = 0, x, res; i < 5000; i++) {
        x = i * 2;
        if (x + 1 >= n) assert(false);
        cout << "? " << a[x] << ' ' << a[x + 1] << endl;
        cin >> res;
        ll f = breakDown(res);
        if (f != -1) {
            work(a[x], f);
            return;
        }
    }
}
int main() {
    calPrime();
    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        solve();
        cout << "!";
        for (int i = 1; i <= n; i++) cout << " " << b[i];
        cout << endl;
    }
}