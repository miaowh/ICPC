#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int ask(int a, int b, int c) {
    cout << "? " << a << ' ' << b << ' ' << c << endl;
    int ret;
    cin >> ret;
    return ret;
}
void guess(int a, int b) { cout << "! " << a << ' ' << b << endl; }

int main() {
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;

        int mx1 = -1, idx = -1, cnt1 = 0;
        for (int i = 3; i <= n; i++) {
            int res = ask(1, 2, i);
            if (res > mx1) {
                mx1 = res;
                idx = i;
                cnt1 = 1;
            } else if (res == mx1)
                cnt1++;
        }

        int a = idx;
        int mx2 = -1, cnt2 = 0;
        for (int i = 2; i <= n; i++) {
            if (i == a) continue;
            int res = ask(1, a, i);
            if (res > mx2) {
                mx2 = res;
                idx = i;
                cnt2 = 1;
            } else if (res == mx2)
                cnt2++;
        }
        if (mx2 > mx1)
            guess(a, idx);
        else if (cnt1 == n - 2)
            guess(1, 2);
        else if (cnt2 == n - 2)
            guess(1, a);
        else
            guess(2, a);
        assert(mx2 >= mx1);
    }
}

/*
Suppose:
max(a1,a2,ak) = T
max(a1,ak,ai) = M

if a1 <= ak <= a2, then the answer is between a1 and a2.
else the anwser may be (ak, ai), (a1, ak) or (a2, ak).

*/