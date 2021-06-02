#include <cstdio>
#include <queue>
using namespace std;
const int maxn = 305;
int dx[8] = {-2, -2, -1, -1, 1, 1, 2, 2};
int dy[8] = {-1, 1, -2, 2, -2, 2, -1, 1};
int n, sx, sy, ex, ey;
int vis[maxn][maxn];
int num[maxn][maxn];
struct Node {
  int x, y, t, cnt;
};
int bfs() {
  if (sx == ex && sy == ey) return 0;
  queue<Node> q;
  q.push({sx, sy, 1, 0});
  q.push({ex, ey, 2, 0});
  vis[sx][sy] = 1;
  vis[ex][ey] = 2;
  while (!q.empty()) {
    Node now = q.front();
    q.pop();
    for (int i = 0, nx, ny; i < 8; i++) {
      nx = now.x + dx[i];
      ny = now.y + dy[i];
      if (nx < 0 || ny < 0 || nx >= n || ny >= n) continue;
      if (vis[nx][ny] == now.t) continue;
      if (vis[nx][ny] == 0) {
        vis[nx][ny] = now.t;
        num[nx][ny] = now.cnt + 1;
        q.push({nx, ny, now.t, now.cnt + 1});
      } else
        return now.cnt + num[nx][ny] + 1;
    }
  }
  return -1;
}
int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    scanf("%d%d%d%d", &sx, &sy, &ex, &ey);
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++) vis[i][j] = 0, num[i][j] = 0;
    printf("%d\n", bfs());
  }
}