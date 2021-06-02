#include <bits/stdc++.h>
using namespace std;
int n;

vector<int> calPriFac(int n) {
    vector<int> ret;
    for (int i = 2; 1LL * i * i <= n; i++) {
        if (n % i == 0) {
            ret.push_back(i);
            while (n % i == 0) n /= i;
        }
    }
    if (n > 1) ret.push_back(n);
    return ret;
}
vector<int> calFac(int n) {
    vector<int> ret;
    for (int i = 2; 1LL * i * i <= n; i++) {
        if (n % i == 0) {
            ret.push_back(i);
            if (i * i != n) ret.push_back(n / i);
        }
    }
    ret.push_back(n);
    return ret;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        auto priFac = calPriFac(n);
        auto fac = calFac(n);

        if (priFac.size() == 1) {
            for (auto &u : fac) printf("%d ", u);
            puts("\n0");
        } else if (priFac.size() == 2 && fac.size() == 3) {
            printf("%d %d %d\n1\n", priFac[0], priFac[0] * priFac[1],
                   priFac[1]);
        } else {
            vector<int> nxt(priFac.size());
            unordered_map<int, bool> vis;
            for (int i = 0; i < priFac.size(); i++) {
                vis[priFac[i]] = true;
                int j = (i + 1) % priFac.size();
                for (auto &u : fac)
                    if (!vis.count(u) && u % priFac[i] == 0 &&
                        u % priFac[j] == 0) {
                        vis[u] = true;
                        nxt[i] = u;
                        break;
                    }
            }
            for (int i = 0; i < priFac.size(); i++) {
                printf("%d ", priFac[i]);
                for (auto &u : fac) {
                    if (!vis.count(u) && u % priFac[i] == 0) {
                        vis[u] = true;
                        printf("%d ", u);
                    }
                }
                printf("%d ", nxt[i]);
            }
            puts("\n0\n");
        }
    }
}