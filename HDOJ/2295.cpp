#include <bits/stdc++.h>
using namespace std;
using pdd = pair<double, double>;
pdd cities[100], radios[100];
const double eps = 1e-7;
int n, m, k;

const int maxn = 1e6;
struct DLX {
    int L[maxn], R[maxn], U[maxn], D[maxn];
    int col[maxn], row[maxn];
    int sz[maxn], rowPtr[maxn], idx;
    int maxDep, stk[maxn];
    int ans;

    void remove(int c) {
        // remove the c-th column and corresponding rows
        L[R[c]] = L[c];
        R[L[c]] = R[c];
        for (int i = D[c]; i != c; i = D[i])
            for (int j = R[i]; j != i; j = R[j])
                U[D[j]] = U[j], D[U[j]] = D[j], --sz[col[j]];
    }

    void recover(int c) {
        // recover the c-th column and corresponding rows
        for (int i = U[c]; i != c; i = U[i])
            for (int j = L[i]; j != i; j = L[j])
                U[D[j]] = D[U[j]] = j, ++sz[col[j]];
        L[R[c]] = R[L[c]] = c;
    }

    void build(int m) {
        // 0 is a head node. column counts from 1. row can count from 0.
        for (int i = 0; i <= m; i++) {
            L[i] = i - 1, R[i] = i + 1;
            U[i] = D[i] = i;
        }
        L[0] = m, R[m] = 0, idx = m;
        memset(sz, 0, sizeof(sz));
        memset(rowPtr, 0, sizeof(rowPtr));
    }

    void insert(int r, int c) {
        // insert an element in r-th row, c-th column
        row[++idx] = r, col[idx] = c, ++sz[c];
        U[idx] = c, D[idx] = D[c], U[D[c]] = idx, D[c] = idx;
        if (!rowPtr[r])
            rowPtr[r] = L[idx] = R[idx] = idx;
        else {
            int x = rowPtr[r];
            L[idx] = x, R[idx] = R[x];
            L[R[x]] = idx, R[x] = idx;
        }
    }

    int cal() {
        vector<bool> vis(m + 1);
        int ret = 0;
        for (int i = R[0]; i; i = R[i]) {
            if (vis[i]) continue;
            vis[i] = true;
            ++ret;
            for (int j = D[i]; j != i; j = D[j])
                for (int v = R[j]; v != j; v = R[v]) vis[v] = true;
        }
        return ret;
    }
    bool dance(int dep) {
        if (dep + cal() > maxDep) return false;
        if (!R[0]) {
            maxDep = dep;
            return true;
        }
        int c = R[0];
        for (int i = R[0]; i; i = R[i])
            if (sz[i] < sz[c]) c = i;
        remove(c);
        for (int i = D[c]; i != c; i = D[i]) {
            stk[dep] = row[i];
            for (int j = R[i]; j != i; j = R[j]) remove(col[j]);
            if (dance(dep + 1)) return true;
            for (int j = L[i]; j != i; j = L[j]) recover(col[j]);
        }
        recover(c);
        return false;
    }
} dlx;

double len(const pdd &a, const pdd &b) {
    return (a.first - b.first) * (a.first - b.first) +
           (a.second - b.second) * (a.second - b.second);
}
bool ok(double r) {
    vector<bool> vis[100];
    for (int i = 0; i < n; i++) {
        bool f = false;
        for (int j = 0; j < m; j++) {
            if (len(cities[i], radios[j]) <= r * r) {
                f = true;
                vis[j].push_back(true);
            } else
                vis[j].push_back(false);
        }
        if (!f) return false;
    }
    dlx.build(n);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (vis[i][j]) dlx.insert(i, j + 1);
        }
    }
    return dlx.dance(0);
}
int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &n, &m, &k);
        for (int i = 0; i < n; i++)
            scanf("%lf%lf", &cities[i].first, &cities[i].second);
        for (int i = 0; i < m; i++)
            scanf("%lf%lf", &radios[i].first, &radios[i].second);
        double l = 0, r = 2000, ans = -1;
        while (abs(r - l) > eps) {
            double mid = (l + r) / 2;
            if (ok(mid)) {
                ans = mid;
                r = l;
            } else
                l = r;
        }
        printf("%.6f\n", ans);
    }
}