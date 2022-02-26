#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;
bool vis[MAXN][MAXN];
int dr[] = {-1, 0, 0, 1}, dc[] = {0, -1, 1, 0};
int ans = 0;
void dfs(const vector<vector<int>> &Board, int r, int c, int val, int pos) {
    vis[r][c] = true;
    val = val * 10 + Board[r][c];
    if (pos == 3) {
        ans = max(ans, val);
        vis[r][c] = false;
        return;
    }
    int R = Board.size(), C = Board[0].size();
    for (int i = 0; i < 4; i++) {
        int nr = r + dr[i], nc = c + dc[i];
        if (nr < R && nc < C && nr >= 0 && nc >= 0 && vis[nr][nc] == false) {
            dfs(Board, nr, nc, val, pos + 1);
        }
    }
    vis[r][c] = false;
}
int solution(vector<vector<int>> &Board) {
    for (int i = 0; i < Board.size(); i++) {
        for (int j = 0; j < Board[i].size(); j++) {
            dfs(Board, i, j, 0, 0);
        }
    }
    return ans;
}
int main() {
    // vector<vector<int>> Board = {};
    // vector<vector<int>> Board = {{1, 1, 1}, {1, 3, 4}, {1, 4, 3}};
    // vector<vector<int>> Board = {{0, 1, 5, 0, 0}};
    vector<vector<int>> Board = {
        {9, 1, 1, 0, 7}, {1, 0, 2, 1, 0}, {1, 9, 1, 1, 0}};

    cout << solution(Board) << endl;
}