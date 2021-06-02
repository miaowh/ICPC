#include <cstdio>
#include <queue>
#include <set>
#include <vector>
using namespace std;
const int maxn = 55;
char maze[maxn][maxn];
typedef pair<int, int> pii;
int n, m;
int dr[] = {-1, 0, 0, 1};
int dc[] = {0, -1, 1, 0};
bool vis[maxn][maxn], ok[maxn * maxn];
vector<pii> G[maxn * maxn];
inline int id(int r, int c) { return r * n + c; }

struct Edge {
  int u, v, w;
  bool operator<(const Edge &rhs) const {
    if (w == rhs.w) {
      if (u == rhs.u) {
        return v < rhs.v;
      } else
        return u < rhs.u;
    }
    return w < rhs.w;
  }
};

void bfs(int r, int c) {
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++) vis[i][j] = 0;
  queue<Edge> q;
  q.push(Edge{r, c, 0});
  vis[r][c] = 1;
  while (!q.empty()) {
    Edge now = q.front();
    q.pop();
    for (int i = 0; i < 4; i++) {
      int nr = now.u + dr[i];
      int nc = now.v + dc[i];
      if (nr >= 0 && nr < n && nc >= 0 && nc < m && maze[nr][nc] != '#' &&
          !vis[nr][nc]) {
        int w = now.w + 1;
        if (maze[nr][nc] == 'A' || maze[nr][nc] == 'S') {
          int id1 = id(r, c);
          int id2 = id(nr, nc);
          G[id1].push_back(make_pair(id2, w));
          G[id2].push_back(make_pair(id1, w));
        }
        vis[nr][nc] = 1;
        q.push(Edge{nr, nc, w});
      }
    }
  }
}

set<Edge> edges;

int par[maxn * maxn];
int find(int x) { return x == par[x] ? x : par[x] = find(par[x]); }
bool same(int x, int y) { return find(x) == find(y); }
void merge(int x, int y) {
  x = find(x);
  y = find(y);
  par[x] = y;
}
int kruskal() {
  int ret = 0;
  for (int i = 0; i < n * m; i++) par[i] = i;
  while (edges.size()) {
    Edge e = *edges.begin();
    if (same(e.u, e.v))
      edges.erase(edges.begin());
    else {
      ret += e.w;
      merge(e.u, e.v);
      int u = 0;
      if (!ok[e.u]) {
        u = e.u;
        ok[u] = 1;
        for (int k = 0; k < G[u].size(); k++) {
          int v = G[u][k].first;
          int w = G[u][k].second;
          edges.insert(Edge{u, v, w});
        }
      }
      if (!ok[e.v]) {
        u = e.v;
        ok[u] = 1;
        for (int k = 0; k < G[u].size(); k++) {
          int v = G[u][k].first;
          int w = G[u][k].second;
          edges.insert(Edge{u, v, w});
        }
      }
    }
  }
  return ret;
}
int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &m, &n);
    char c;
    while ((c = getchar() == ' '))
      ;
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
        maze[i][j] = '.', G[id(i, j)].clear(), ok[id(i, j)] = 0;
    for (int i = 0; i < n; i++) gets(maze[i]);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (maze[i][j] == 'A' || maze[i][j] == 'S') {
          bfs(i, j);
          if (maze[i][j] == 'S') {
            int u = id(i, j);
            ok[u] = 1;
            for (int k = 0; k < G[u].size(); k++) {
              int v = G[u][k].first;
              int w = G[u][k].second;
              edges.insert(Edge{u, v, w});
            }
          }
        }
      }
    }
    int ans = kruskal();
    printf("%d\n", ans);
  }
}

/*

2
6 5
#####.
#A#A##
#.#.A#
#S..##
#####.
7 7
#####..
#AAA###
#....A#
#.S.###
#.....#
#AAA###
#####..
 */

/*


在召唤师峡谷中存在这么一种珍贵的能量，它可以大大的增加小喵的战斗力。这种能量散落在召唤师峡谷的一些地方，
我们可以把召唤师峡谷想象成二维平面，其中$#$表示墙壁，$.$表示空地，$A$表示这种能量，$S$表示小喵的起始点。
每次小喵可以选择上下左右四个方向的其中一个方向走一格（不能走到墙壁）或者停留原地，每走一格小喵会消耗$1$点
自身的体力，停留原地则不消耗体力。

小喵希望尽快的收集完所有能量，于是它决定使用自己的技能。小喵的技能是无限分身，即小喵释放技能后就会有很多
分身，这些分身会听小喵的操控。但是这些分身走路所消耗的体力也会算在小喵的身上。比如下面这种情况：

#####
A.S.A
#####

如果小喵不使用分身，则小喵需要从$S$先走到其中的一个$A$，再走到另一个$A$，消耗的体力是$2
+ 4$。
而如果小喵在$S$点使用分身，则小喵可以控制另一个分身往一个方向走，自己往另一个方向走，消耗的体力是$2
+ 2$。

因为小喵的分身和小喵本体并无差别，因此小喵的分身也可以继续使用分身，最后的体力也是算在小喵本体。

需要注意的是：

小喵的法力值只能够支持一次技能的释放。

小喵进入游戏时法力值是满状态的。

小喵在吃到能量后，法力值会回复到满状态。

各个分身之间的法力值不会相互影响。即如果一个小喵（可能是分身也可能是本体）吃到能量，那么仅仅是吃到能量的小喵的法力值会恢复，并不会影响其它小喵。

小喵释放技能后，法力值变为空，释放出来的分身的法力值也为空。




你的任务是求出小喵收集完所有能量后所消耗的最少的体力。


对于第一样例：
设左上角的坐标为$(0,0)$

小喵在\t{S}点时使用分身后，小喵向坐标为$(1,1)$的\t{A}点出发，分身向坐标为$(1,3)$的\t{A}点出发。
等到分身到达$(1,3)$，它可以选择分身，让分身去走到坐标为$(2,4)$的\t{A}点；也可以选择不分身，直接走到$(2,4)$
，这两种方式所消耗的体力时一样的。那么总的体力就是$2 + 4 + 2$。
*/