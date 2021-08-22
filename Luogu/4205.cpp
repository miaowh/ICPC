#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
char maze[10][11];
int pos[10][10];
int vis[20];
vector<vector<pii>> table = {
    {{0, 0}, {1, 0}, {0, 1}},                   // A
    {{0, 0}, {0, 1}, {0, 2}, {0, 3}},           // B
    {{0, 0}, {1, 0}, {0, 1}, {0, 2}},           // C
    {{0, 0}, {1, 0}, {0, 1}, {1, 1}},           // D
    {{0, 0}, {1, 0}, {2, 0}, {2, 1}, {2, 2}},   // E
    {{0, 0}, {0, 1}, {1, 1}, {0, 2}, {0, 3}},   // F
    {{0, 0}, {1, 0}, {0, 1}, {0, 2}, {1, 2}},   // G
    {{0, 0}, {1, 0}, {0, 1}, {1, 1}, {0, 2}},   // H
    {{0, 0}, {0, 1}, {0, 2}, {1, 2}, {1, 3}},   // I
    {{0, 0}, {-1, 1}, {0, 1}, {1, 1}, {0, 2}},  // J
    {{0, 0}, {1, 0}, {1, 1}, {2, 1}, {2, 2}},   // K
    {{0, 0}, {1, 0}, {0, 1}, {0, 2}, {0, 3}},   // L
};

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

    bool dance(int dep) {
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

struct Node {
    int type;
    int rotate, filp;
    int x, y;
};
vector<Node> nodes;

pii rotate(pii p) { return {-p.second, p.first}; }
vector<pii> getPs(Node a) {
    vector<pii> ps = table[a.type];
    for (auto &p : ps) {
        for (int i = 0; i < a.rotate; i++) p = rotate(p);
        p.second *= a.filp;
        p.first += a.x, p.second += a.y;
    }
    return ps;
}
void check(int type, int x, int y, int r, int filp) {
    Node a = Node{type, r, filp, x, y};
    vector<pii> ps = getPs(a);
    for (auto &p : ps) {
        if (p.first >= 0 && p.first < 10 && p.second >= 0 && p.second < 10 &&
            p.first >= p.second && maze[p.first][p.second] == '.')
            continue;
        return;
    }
    nodes.push_back(a);
}

int main() {
    int idx = 0, tot = 0;
    dlx.build(67);
    for (int i = 0; i < 10; i++) {
        scanf("%s", maze[i]);
        for (int j = 0; j <= i; j++) {
            pos[i][j] = ++tot;
            if (maze[i][j] == '.') continue;
            int type = maze[i][j] - 'A';
            if (!vis[type]) {
                vis[type] = ++idx;
                nodes.push_back({type, 0, 0, 0, 0});
                dlx.insert(idx, 56 + type);
            }
            dlx.insert(idx, pos[i][j]);
        }
    }
    for (int i = 0; i < 12; i++) {
        if (!vis[i]) {
            for (int x = 0; x < 10; x++) {
                for (int y = 0; y <= x; y++) {
                    for (int r = 0; r < 4; r++) {
                        check(i, x, y, r, 1);
                        check(i, x, y, r, -1);
                    }
                }
            }
        }
    }

    for (int i = 0; i < nodes.size(); i++) {
        if (vis[nodes[i].type]) continue;
        auto ps = getPs(nodes[i]);
        dlx.insert(++idx, 56 + nodes[i].type);
        for (auto &p : ps) dlx.insert(idx, pos[p.first][p.second]);
    }

    if (!dlx.dance(0)) {
        puts("No solution");
        return 0;
    }
    for (int i = 0; i < dlx.maxDep; i++) {
        int row = dlx.stk[i] - 1;
        auto x = nodes[row];
        if (vis[x.type]) continue;
        auto ps = getPs(x);
        for (auto &p : ps) maze[p.first][p.second] = 'A' + x.type;
    }
    for (int i = 0; i < 10; i++) printf("%s\n", maze[i]);
}