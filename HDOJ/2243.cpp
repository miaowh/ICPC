// ybmj
#include <bits/stdc++.h>
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
typedef unsigned long long ull;
typedef pair<ll, ll> pll;
#define my_unique(a) a.resize(distance(a.begin(), unique(a.begin(), a.end())))
#define my_sort_unique(c) (sort(c.begin(), c.end())), my_unique(c)
const int INF = 0x3f3f3f3f;
const int NINF = 0xc0c0c0c0;
const double PI = acos(-1.0);
const int maxn = 35;
struct Trie {
    int ch[maxn][26], f[maxn], val[maxn];
    int sz, rt;
    int newnode() {
        memset(ch[sz], -1, sizeof(ch[sz])), val[sz] = 0;
        return sz++;
    }
    void init() { sz = 0, rt = newnode(); }
    int idx(char c) { return c - 'a'; }
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
        for (int c = 0; c < 26; c++) {
            if (~ch[rt][c])
                f[ch[rt][c]] = rt, q.push(ch[rt][c]);
            else
                ch[rt][c] = rt;
        }
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            val[u] |= val[f[u]];
            for (int c = 0; c < 26; c++) {
                if (~ch[u][c])
                    f[ch[u][c]] = ch[f[u]][c], q.push(ch[u][c]);
                else
                    ch[u][c] = ch[f[u]][c];
            }
        }
    }
} trie;

namespace Matrix {
// Matrix mat(row, vec(col));
typedef vector<ull> vec;
typedef vector<vec> mat;
mat mul(mat& A, mat& B) {
    mat C(A.size(), vec(B[0].size()));
    for (int i = 0; i < A.size(); i++)
        for (int k = 0; k < B.size(); k++)
            if (A[i][k])
                for (int j = 0; j < B[0].size(); j++)
                    C[i][j] = (C[i][j] + A[i][k] * B[k][j]);
    return C;
}
mat Pow(mat A, ull n) {
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
//	/*
#ifndef ONLINE_JUDGE
    freopen("1.in", "r", stdin);
    freopen("1.out", "w", stdout);
#endif
    //	*/
    std::ios::sync_with_stdio(false);
    ull n, l;
    while (cin >> n >> l) {
        trie.init();
        string pat;
        for (int i = 0; i < n; i++) {
            cin >> pat;
            trie.insert(pat.c_str());
        }
        trie.build();
        ull ans = 0;

        Matrix::mat B(2, Matrix::vec(2));
        B[0][0] = 26;
        B[0][1] = B[1][1] = 1;
        B = Matrix::Pow(B, l + 1);
        ans += B[0][1];
        // ----
        int row = trie.sz * 2;
        Matrix::mat A(row, Matrix::vec(row));
        for (int i = 0; i < row / 2; i++) {
            if (trie.val[i]) continue;
            for (int j = 0; j < 26; j++) {
                if (trie.val[trie.ch[i][j]]) continue;
                A[i][trie.ch[i][j]]++;
            }
        }
        for (int i = 0; i < row; i++) {
            for (int j = row / 2; j < row; j++) {
                if (j - i == row / 2 || j - i == 0) A[i][j]++;
            }
        }
        A = Matrix::Pow(A, l + 1);
        for (int i = row / 2; i < row; i++) {
            ans -= A[0][i];
        }
        cout << ans << endl;
    }
}