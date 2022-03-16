#include <bits/stdc++.h>
using namespace std;

string a[10], b[10];

using pii = pair<int, int>;
vector<pii> kills;

bool vis[10][10];
int dx[] = {-1, 0, 0, 1};
int dy[] = {0, 1, -1, 0};
int bIdx[10];

int tot = 0;
void dfs(int x, int y) {
    tot++;
    vis[x][y] = 1;
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx < 0 || ny < 0 || nx > 7 || ny > 7 || vis[nx][ny] ||
            a[x][y] != a[nx][ny])
            continue;
        dfs(nx, ny);
    }
}
int work(int x, int y, char op) {
    tot = 0;
    memset(vis, 0, sizeof(vis));
    dfs(x, y);
    int ret = tot;

    if (op == 'w') {
        for (int j = 0; j < 8; j++) {
            int k = 0;
            for (int i = 0; i < 8; i++) {
                if (!vis[i][j]) a[k++][j] = a[i][j];
            }
            for (; k < 8; k++) {
                a[k][j] = b[j][bIdx[j]++];
            }
        }
    } else if (op == 'd') {
        for (int j = 0; j < 8; j++) {
            int k = 7;
            for (int i = 7; i >= 0; i--) {
                if (!vis[i][j]) a[k++][j] = a[i][j];
            }
            for (; k >= 0; k--) {
                a[k][j] = b[j][bIdx[j]++];
            }
        }
    } else if (op == 'a') {
        for (int i = 0; i < 8; i++) {
            int k = 0;
            for (int j = 0; j < 8; j++) {
                if (!vis[i][j]) a[i][k++] = a[i][j];
            }
            for (; k < 8; k++) {
                a[i][k] = b[i][bIdx[i]++];
            }
        }
    } else {
        for (int i = 0; i < 8; i++) {
            int k = 7;
            for (int j = 7; j >= 0; j--) {
                if (!vis[i][j]) a[i][k++] = a[i][j];
            }
            for (; k >= 0; k--) {
                a[i][k] = b[i][bIdx[i]++];
            }
        }
    }

    return ret;
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < 8; i++) cin >> a[i];
    for (int i = 0; i < 8; i++) cin >> b[i];
    char op;
    for (int i = 0, x, y; i < n; i++) {
        cin >> x >> y >> op;
        x--, y--;
        cout << work(x, y, op) << '\n';
    }
}
/*
2
rbbbrrrb
ggggbrbr
rrrggbrr
gbrgbrrr
bgbgrrrg
bgbgbrrb
rggrgggg
bgbrgrgr
bbrgggggbbgbbbrg
bbgbrgbgbbgbbbrg
brgbgbbggbbgbbbr
gbbgbbbrggrbbgrb
bgrbbrgggrbrgbrr
brgbrgbrgrgbrgbr
brbbrbbbrbrrggrg
ggrbrgbgbrgggrbr
1 5 w
1 4 d


rbbb   b
ggggb br
rrrggbrr
gbrgbrrr
bgbgrrrg
bgbgbrrb
rggrgggg
bgbrgrgr

rbbbb b b
ggggb br
rrrggbrr
gbrgbrrr
bgbgrrrg
bgbgbrrb
rggrgggg
bgbrgrgr
*/