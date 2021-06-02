#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
const int maxn = 1e5 + 5;
int a[maxn];

int main() {
    int n, q;
    scanf("%d%d", &n, &q);
    set<int> pos;
    for (int i = 0; i < n; i++) scanf("%d", a + i), pos.insert(a[i]);
    sort(a, a + n);
    multiset<int> val;
    for (int i = 0; i < n - 1; i++) val.insert(a[i + 1] - a[i]);
    int ans = *pos.rbegin() - *pos.begin();
    if (!val.empty()) ans -= *val.rbegin();
    printf("%d\n", ans);
    for (int i = 0, x, y; i < q; i++) {
        scanf("%d%d", &x, &y);
        auto itr = pos.upper_bound(y);
        auto itl = pos.lower_bound(y);
        int l = -1, r = 2e9;
        if (itr != pos.end()) r = *itr;
        if (itl != pos.begin()) l = *(--itl);
        if (x == 1) {
            if (r != 2e9) val.insert(r - y);
            if (l != -1) val.insert(y - l);
            if (l != -1 && r != 2e9) val.erase(val.find(r - l));
            pos.insert(y);
        } else {
            if (r != 2e9) val.erase(val.find(r - y));
            if (l != -1) val.erase(val.find(y - l));
            if (l != -1 && r != 2e9) val.insert(r - l);
            pos.erase(y);
        }
        ans = 0;
        if (!pos.empty()) ans = *pos.rbegin() - *pos.begin();
        if (!val.empty()) ans -= *val.rbegin();
        printf("%d\n", ans);
    }
}
