#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>
using namespace std;
#define ll long long
#define RG register
#define MAX 55555
inline int read() {
    RG int x = 0, t = 1;
    RG char ch = getchar();
    while ((ch < '0' || ch > '9') && ch != '-') ch = getchar();
    if (ch == '-') t = -1, ch = getchar();
    while (ch <= '9' && ch >= '0') x = x * 10 + ch - 48, ch = getchar();
    return x * t;
}
struct Line {
    int v, next;
} e[MAX * 3];
int h[MAX], cnt = 1;
int n, m, fa[MAX], f[MAX][2], dfn[MAX], low[MAX], tim;
inline void Add(int u, int v) {
    e[cnt] = (Line){v, h[u]};
    h[u] = cnt++;
}
void dp(int u, int y) {
    int t0, t1, f0 = 0, f1 = 0;
    for (int i = y; i != u; i = fa[i]) {
        t0 = f0 + f[i][0];
        t1 = f1 + f[i][1];
        f0 = max(t0, t1);
        f1 = t0;
    }
    f[u][0] += f0;
    f0 = 0;
    f1 = -1e9;
    for (int i = y; i != u; i = fa[i]) {
        t0 = f0 + f[i][0];
        t1 = f1 + f[i][1];
        f0 = max(t0, t1);
        f1 = t0;
    }
    f[u][1] += f1;
}
void dfs(int u, int ff) {
    fa[u] = ff;
    dfn[u] = low[u] = ++tim;
    f[u][1] = 1;
    f[u][0] = 0;
    for (int i = h[u]; i; i = e[i].next) {
        int v = e[i].v;
        if (!dfn[v])
            dfs(v, u), low[u] = min(low[u], low[v]);
        else if (v != ff)
            low[u] = min(low[u], dfn[v]);
        if (low[v] > dfn[u])
            f[u][1] += f[v][0], f[u][0] += max(f[v][0], f[v][1]);
    }
    for (int i = h[u]; i; i = e[i].next)
        if (fa[e[i].v] != u && dfn[u] < dfn[e[i].v]) dp(u, e[i].v);
}
int main() {
    n = read();
    m = read();
    for (int i = 1; i <= m; ++i) {
        int u = read(), v = read();
        Add(u, v);
        Add(v, u);
    }
    dfs(1, 0);
    printf("%d\n", max(f[1][0], f[1][1]));
    return 0;
}