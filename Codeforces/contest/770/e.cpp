#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 6;
const int INF = 0x3f3f3f3f;
struct Edge {
    int u, v;
    int cap, flow;
    Edge(int u_, int v_, int cap_, int flow_)
        : u(u_), v(v_), cap(cap_), flow(flow_) {}
};

struct Dinic {
    int n, m, s, t;  //结点数，边数（包括反向弧），源点编号和汇点编号
    vector<Edge> edges;  //边表。edge[e]和edge[e^1]互为反向弧
    vector<int> G[maxn];  //邻接表，G[i][j]表示节点i的第j条边在e数组中的序号
    bool vis[maxn];  // BFS使用
    int d[maxn];     //从起点到i的距离
    int cur[maxn];   //当前弧下标
    void init(int n) {
        this->n = n;
        for (int i = 0; i <= n; i++) G[i].clear();
        edges.clear();
    }
    int AddEdge(int from, int to, int cap) {
        // cerr << from << "  " << to << " " << cap << endl;
        edges.emplace_back(from, to, cap, 0);
        edges.emplace_back(to, from, 0, 0);
        m = edges.size();
        G[from].push_back(m - 2);
        G[to].push_back(m - 1);
        return m - 2;
    }
    bool BFS() {
        for (int i = 0; i <= n; ++i) vis[i] = false, d[i] = 0;
        queue<int> q;
        q.push(s);
        d[s] = 0;
        vis[s] = 1;
        while (!q.empty()) {
            int x = q.front();
            q.pop();
            for (int i = 0, v; i < G[x].size(); i++) {
                Edge &e = edges[G[x][i]];
                v = e.v;
                if (!vis[v] && e.cap > e.flow) {
                    vis[v] = 1;
                    d[v] = d[x] + 1;
                    q.push(v);
                }
            }
        }
        return vis[t];
    }
    int DFS(int x, int a) {
        if (x == t || a == 0) return a;
        int flow = 0, f;
        for (int &i = cur[x], v; i < G[x].size(); i++) {  //从上次考虑的弧
            Edge &e = edges[G[x][i]];
            v = e.v;
            if (d[x] + 1 == d[v] && (f = DFS(v, min(a, e.cap - e.flow))) > 0) {
                e.flow += f;
                edges[G[x][i] ^ 1].flow -= f;
                flow += f;
                a -= f;
                if (a == 0) break;
            }
        }
        return flow;
    }
    int Maxflow(int s, int t) {
        this->s = s, this->t = t;
        int flow = 0;
        while (BFS()) {
            for (int i = 0; i <= n; i++) cur[i] = 0;
            flow += DFS(s, INF);
        }
        return flow;
    }
} dinic;

bool work() {
    int m;
    scanf("%d", &m);
    vector<int> num(m);
    vector<vector<int>> vec(m);
    map<int, int> id, cnt;
    vector<vector<char>> ans(m);

    int idNum = 0;
    for (int k = 0; k < m; k++) {
        scanf("%d", &num[k]);
        ans[k].resize(num[k]);
        vec[k].resize(num[k]);
        for (int i = 0, u; i < num[k]; i++) {
            scanf("%d", &vec[k][i]);
            cnt[vec[k][i]]++;
            if (!id[vec[k][i]]) id[vec[k][i]] = ++idNum;
        }
    }
    int sum = accumulate(num.begin(), num.end(), 0);

    dinic.init(sum + m + idNum + 1);

    int fcnt = 0;
    map<int, int> rid;
    for (int i = 0; i < m; i++) {
        if (num[i] & 1) return false;
        dinic.AddEdge(0, i + 1, num[i] / 2);

        for (int j = 0; j < num[i]; j++) {
            dinic.AddEdge(i + 1, m + 1 + fcnt, 1);
            dinic.AddEdge(m + 1 + fcnt, sum + m + id[vec[i][j]], 1);
            rid[m + 1 + fcnt] = j;
            fcnt++;
        }
    }

    int mxFlow = 0;
    for (auto &[u, i] : id) {
        if (cnt[u] & 1) return false;
        dinic.AddEdge(sum + m + i, sum + m + idNum + 1, cnt[u] / 2);
        mxFlow += cnt[u];
    }

    int flow = dinic.Maxflow(0, sum + m + idNum + 1);

    if (flow * 2 != mxFlow) return false;

    puts("YES");
    for (auto &e : dinic.edges) {
        if (e.u >= 1 and e.u <= m and e.v >= m + 1 and e.v <= sum + m and
            e.flow == 1) {
            int i = e.u - 1;
            int j = rid[e.v];
            ans[i][j] = 'L';
        }
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < num[i]; j++)
            if (ans[i][j] == 'L')
                printf("L");
            else
                printf("R");
        puts("");
    }
    return true;
}

int main() {
    if (!work()) puts("NO");
}

/*
1, 1, 1, 2
3, 3, 3, 4
1, 3


1, 1, 3, 2
1, 1
3, 2

average in overall
average in local

dinic TLE
*/