#include <bits/stdc++.h>
using namespace std;
const int MAXN = 105;
const int MAXM = 100005;
string ans[MAXN];
int solvedQues[MAXN], peopleSolved[MAXM];

int work() {
    for (int i = 0; i < 100; i++) {
        solvedQues[i] = 0;
        for (auto &c : ans[i]) solvedQues[i] += c == '1';
    }
    for (int i = 0; i < 10000; i++) {
        peopleSolved[i] = 0;
        for (int j = 0; j < 100; j++) peopleSolved[i] += ans[j][i] == '1';
    }

    vector<int> idx(10000);
    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(),
         [&](int a, int b) { return peopleSolved[a] > peopleSolved[b]; });

    vector<vector<int>> pre(100);

    vector<int> ret;
    for (int i = 0; i < 100; i++) {
        bool flag = true;
        pre[i].resize(10000);
        for (int j = 0; j < 10000; j++) {
            pre[i][j] = ans[i][idx[j]] == '1';
            if (j) pre[i][j] += pre[i][j - 1];
        }

        int sz = 500;
        int end = pre[i][9999] - pre[i][9999 - sz];
        if (end * 2.5 > sz) ret.push_back(i);
    }

    if (ret.empty()) assert(false);
}

int main() {
    int T, p, kase = 1;
    cin >> T >> p;
    while (T--) {
        for (int i = 0; i < 100; i++) cin >> ans[i];
        cout << "Case #" << kase++ << ": " << work() << endl;
    }
}
