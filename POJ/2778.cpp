// ybmj
// #include <bits/stdc++.h>
#include <string.h>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
#define lson (rt << 1)
#define rson (rt << 1 | 1)
#define lson_len (len - (len >> 1))
#define rson_len (len >> 1)
#define pb(x) push_back(x)
#define clr(a, x) memset(a, x, sizeof(a))
#define mp(x, y) make_pair(x, y)
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
#define my_unique(a) a.resize(distance(a.begin(), unique(a.begin(), a.end())))
#define my_sort_unique(c) (sort(c.begin(), c.end())), my_unique(c)
const int INF = 0x3f3f3f3f;
const int NINF = 0xc0c0c0c0;
const double PI = acos(-1.0);
const int mod = 1e5;
const int maxn = 15 * 15;
char pat[15];
struct Trie {
    int ch[maxn][4], f[maxn], val[maxn];
    int sz, rt;
    int newnode() {
        memset(ch[sz], -1, sizeof(ch[sz])), val[sz] = 0;
        return sz++;
    }
    void init() { sz = 0, rt = newnode(); }
    int idx(char c) {
        if (c == 'A') return 0;
        if (c == 'T') return 1;
        if (c == 'G') return 2;
        return 3;
    }
    void insert(const char* s) {
        int u = 0;
        for (int i = 0; s[i]; i++) {
            int c = idx(s[i]);
            if (ch[u][c] == -1) ch[u][c] = newnode();
            u = ch[u][c];
        }
        val[u]++;
    }
    void build() {
        queue<int> q;
        f[rt] = rt;
        for (int c = 0; c < 4; c++) {
            if (~ch[rt][c])
                f[ch[rt][c]] = rt, q.push(ch[rt][c]);
            else
                ch[rt][c] = rt;
        }
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            val[u] |= val[f[u]];
            for (int c = 0; c < 4; c++) {
                if (~ch[u][c])
                    f[ch[u][c]] = ch[f[u]][c], q.push(ch[u][c]);
                else
                    ch[u][c] = ch[f[u]][c];
            }
        }
    }
} trie;

namespace Matrix {
typedef vector<ll> vec;
typedef vector<vec> mat;
mat mul(mat& A, mat& B) {
    mat C(A.size(), vec(B[0].size()));
    for (int i = 0; i < A.size(); i++)
        for (int k = 0; k < B.size(); k++)
            if (A[i][k])
                for (int j = 0; j < B[0].size(); j++)
                    C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % mod;
    return C;
}
mat Pow(mat A, ll n) {
    mat B(A.size(), vec(A.size()));
    for (int i = 0; i < A.size(); i++) B[i][i] = 1;
    while (n) {
        if (n & 1) B = mul(B, A);
        A = mul(A, A);
        n >>= 1;
    }
    return B;
}
}  // namespace Matrix

int main() {
    /*
#ifndef ONLINE_JUDGE
freopen("1.in", "r", stdin);
freopen("1.out", "w", stdout);
#endif
    */
    std::ios::sync_with_stdio(false);
    int n, m;
    scanf("%d%d", &m, &n);
    trie.init();
    for (int i = 0; i < m; i++) {
        scanf("%s", pat);
        trie.insert(pat);
    }
    trie.build();
    Matrix::mat tmp(trie.sz, Matrix::vec(trie.sz));
    for (int i = 0; i < trie.sz; i++) {
        if (trie.val[i]) continue;
        for (int j = 0; j < 4; j++) {
            if (trie.val[trie.ch[i][j]]) continue;
            tmp[i][trie.ch[i][j]]++;
        }
    }
    tmp = Matrix::Pow(tmp, n);
    int ans = 0;
    for (int i = 0; i < trie.sz; i++) ans = (ans + tmp[0][i]) % mod;
    printf("%d\n", ans);
}