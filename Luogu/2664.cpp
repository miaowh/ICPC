/*
    入手点是：每种颜色第一次出现的位置
    因为是一棵树，我们可以考虑记录每种颜色相对于根第一次出现的位置。比如点i的颜色是c[i]，
    根是rt。假设i到rt这条路径上，c[i]这种颜色第一次出现。那么i点对根的其它子树的点的贡献
    就是i点子树的大小（假设那些点到根的路径上没有c[i]这种颜色）。
    于是每次我们就可以算出根的子树之间的贡献，子树内的贡献就递归去算。所以这里肯定要点分治了。
*/
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 5;
using ll = long long;
int c[maxn], sz[maxn], heavySonSz[maxn];
int sz1[maxn], cnt[maxn];
ll ans[maxn], color[maxn];
bool vis[maxn];
vector<int> G[maxn];
int n, rt, treeSz, tot;
ll sum;

void findRoot(int u, int fa) {
    sz[u] = 1, heavySonSz[u] = 0;
    for (auto &v : G[u]) {
        if (v != fa && !vis[v]) {
            findRoot(v, u);
            sz[u] += sz[v];
            heavySonSz[u] = max(heavySonSz[u], sz[v]);
        }
    }
    heavySonSz[u] = max(heavySonSz[u], treeSz - sz[u]);
    if (heavySonSz[u] < heavySonSz[rt]) rt = u;
}

void getSz1(int u, int fa) {
    color[c[u]] = 0;
    sz1[u] = 1;
    for (auto &v : G[u]) {
        if (vis[v] || v == fa) continue;
        getSz1(v, u);
        sz1[u] += sz1[v];
    }
}
void change(int u, int fa, int sign) {
    cnt[c[u]]++;
    for (auto &v : G[u]) {
        if (vis[v] || v == fa) continue;
        change(v, u, sign);
    }
    if (cnt[c[u]] == 1) {
        sum += sign * sz1[u];
        color[c[u]] += sign * sz1[u];
    }
    cnt[c[u]]--;
}
void gao(int u, int fa) {
    cnt[c[u]]++;
    if (cnt[c[u]] == 1) {
        sum -= color[c[u]];
        tot++;
    }
    ans[u] += sum + 1LL * tot * sz1[0];
    for (auto &v : G[u]) {
        if (vis[v] || v == fa) continue;
        gao(v, u);
    }

    cnt[c[u]]--;
    if (cnt[c[u]] == 0) {
        sum += color[c[u]];
        tot--;
    }
}
void cal(int u, int fa) {
    sum = 0;
    getSz1(u, 0);
    change(u, 0, 1);
    ans[u] += sum;
    for (auto &v : G[u]) {
        if (vis[v] || v == fa) continue;
        cnt[c[u]]++;
        change(v, u, -1);
        cnt[c[u]]--;
        sum -= sz1[v];
        color[c[u]] -= sz1[v];
        sz1[0] = sz1[u] - sz1[v];
        gao(v, u);

        sum += sz1[v];
        color[c[u]] += sz1[v];
        cnt[c[u]]++;
        change(v, u, 1);
        cnt[c[u]]--;
    }
}
void dfs(int u) {
    vis[u] = 1;
    cal(u, 0);
    for (auto &v : G[u]) {
        if (vis[v]) continue;
        rt = 0, treeSz = sz[v];
        findRoot(v, u);
        dfs(rt);
    }
}
int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d", &c[i + 1]);
    for (int i = 1, x, y; i < n; i++) {
        scanf("%d%d", &x, &y);
        G[x].push_back(y);
        G[y].push_back(x);
    }
    treeSz = n;
    rt = 0;
    heavySonSz[rt] = 1e9;
    findRoot(1, -1);
    dfs(rt);
    for (int i = 1; i <= n; i++) printf("%lld\n", ans[i]);
}