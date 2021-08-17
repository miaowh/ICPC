#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6;
int score[10][10];
int ANS;
struct DLX {
    int L[maxn], R[maxn], U[maxn], D[maxn];
    int col[maxn], row[maxn];
    int sz[maxn], rowPtr[maxn], idx;
    int n, m;
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

    void build(int r, int c) {
        // 0 is a head node. column counts from 1. row can count from 0.
        n = r, m = c;
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

    bool dance(int dep) {
        if (!R[0]) {
            maxDep = dep;
            ANS = max(ANS, ans);
            return true;
        }
        int c = R[0];
        for (int i = R[0]; i; i = R[i])
            if (sz[i] < sz[c]) c = i;
        remove(c);
        for (int i = D[c]; i != c; i = D[i]) {
            stk[dep] = row[i];

            int r = row[i] - 1;
            ans += (r % 9 + 1) * score[r / 81 + 1][r % 81 / 9 + 1];
            for (int j = R[i]; j != i; j = R[j]) remove(col[j]);
            dance(dep + 1);
            // if (dance(dep + 1)) return true;
            for (int j = L[i]; j != i; j = L[j]) recover(col[j]);
            ans -= (r % 9 + 1) * score[r / 81 + 1][r % 81 / 9 + 1];
        }
        recover(c);
        return false;
    }
} dlx;

int val[10][10];

int main() {
    dlx.build(729, 324);
    for (int i = 1, a; i <= 9; i++) {
        for (int j = 1; j <= 9; j++) {
            scanf("%d", &val[i][j]);
            for (int x = 1; x <= 9; x++) {
                if (val[i][j] && val[i][j] != x) continue;
                int id = (i - 1) * 81 + (j - 1) * 9 + x;
                dlx.insert(id, (i - 1) * 9 + j);
                dlx.insert(id, 81 + (i - 1) * 9 + x);
                dlx.insert(id, 162 + (j - 1) * 9 + x);
                int block = (i - 1) / 3 * 3 + (j - 1) / 3;
                dlx.insert(id, 243 + block * 9 + x);
            }
        }
    }
    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= 9; j++) {
            score[i][j] = 10 - max(abs(i - 5), abs(j - 5));
        }
    }
    ANS = -1;
    dlx.dance(0);
    printf("%d\n", ANS);
}