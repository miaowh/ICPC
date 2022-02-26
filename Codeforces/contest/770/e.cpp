#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e6 + 6, MAXM = 1e6 + 6;
const int INF = 0x3f3f3f3f;
using pii = pair<int, int>;
vector<pii> G[MAXN];
bool Vis[MAXM];
vector<int> Ans;
int EdgeId, CurArc[MAXN];

void addEdge(int u, int v) {
    G[u].push_back({v, EdgeId});
    G[v].push_back({u, EdgeId++});
}
void findEulerCircuit(int u) {
    for (int &i = CurArc[u]; i < G[u].size(); i++) {
        const auto &[v, id] = G[u][i];
        if (Vis[id]) continue;
        Vis[id] = true;
        findEulerCircuit(v);
    }
    Ans.push_back(u);
}

bool work() {
    int m;
    scanf("%d", &m);
    vector<int> num(m);
    vector<vector<int>> vec(m);
    map<int, int> id, rid, cnt;
    map<int, int> ans[m];

    int idNum = m;
    for (int k = 0; k < m; k++) {
        scanf("%d", &num[k]);
        vec[k].resize(num[k]);
        for (int i = 0, u; i < num[k]; i++) {
            scanf("%d", &vec[k][i]);
            cnt[vec[k][i]]++;
            if (!id[vec[k][i]]) {
                rid[idNum] = vec[k][i];
                id[vec[k][i]] = idNum++;
            }
        }
    }
    for (auto &u : cnt)
        if (u.second & 1) return false;

    for (int i = 0; i < m; i++) {
        for (auto &u : vec[i]) {
            addEdge(i, id[u]);
        }
    }

    for (int i = 0; i < m; i++) {
        if (CurArc[i] >= G[i].size()) continue;
        findEulerCircuit(i);
        for (int j = 0; j < Ans.size() - 1; j++) {
            int u = Ans[j], v = Ans[j + 1];
            if (u < m) ans[u][rid[v]]++;
        }
        Ans.clear();
    }

    puts("YES");
    for (int i = 0; i < m; i++) {
        for (auto &u : vec[i]) {
            if (ans[i][u]) {
                printf("L");
                ans[i][u]--;
            } else
                printf("R");
        }
        puts("");
    }
    return true;
}

int main() {
    if (!work()) puts("NO");
}

/*

3
4
1 1 3 2
2
1 1
2
3 2

average in overall
average in local

dinic TLE
*/