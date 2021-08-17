#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6;

struct DLX {
    int L[maxn], R[maxn], U[maxn], D[maxn];
    int col[maxn], row[maxn];
    int sz[maxn], rowPtr[maxn], idx;
    int n, m;
    int ans, stk[maxn];

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
            ans = dep;
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