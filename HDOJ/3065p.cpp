// ybmj
#include <bits/stdc++.h>
using namespace std;
#define lson (rt << 1)
#define rson (rt << 1 | 1)
#define lson_len (len - (len >> 1))
#define rson_len (len >> 1)
#define pb(x) push_back(x)
#define clr(a, x) memset(a, x, sizeof(a))
#define mp(x, y) make_pair(x, y)
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
#define my_unique(a) a.resize(distance(a.begin(), unique(a.begin(), a.end())))
#define my_sort_unique(c) (sort(c.begin(), c.end())), my_unique(c)
const int INF = 0x3f3f3f3f;
const int NINF = 0xc0c0c0c0;
const double PI = acos(-1.0);
const int Types = 100;
char pat[1005][60], t[2000005];
int cnt[1005];
struct Node {
    Node *f, *ch[Types];
    int val;
    Node() {
        val = 0;
        f = nullptr;
        for (int i = 0; i < Types; i++) ch[i] = nullptr;
    }
};
struct Trie {
    vector<Node *> nodes;
    Node *rt;
    void init() {
        rt = new Node();
        nodes.push_back(rt);
    }
    int idx(const char &c) { return c - 0x20; }
    void insert(int id, const char *s) {
        Node *u = rt;
        for (int i = 0, c; s[i]; i++) {
            c = idx(s[i]);
            if (u->ch[c] == nullptr)
                u->ch[c] = new Node(), nodes.push_back(u->ch[c]);
            u = u->ch[c];
        }
        u->val = id;
    }
    void build() {
        queue<Node *> q;
        rt->f = rt;
        for (int i = 0; i < Types; i++) {
            if (rt->ch[i] != nullptr)
                rt->ch[i]->f = rt, q.push(rt->ch[i]);
            else
                rt->ch[i] = rt;
        }
        while (!q.empty()) {
            Node *u = q.front();
            q.pop();
            for (int i = 0; i < Types; i++) {
                if (u->ch[i] != nullptr)
                    u->ch[i]->f = u->f->ch[i], q.push(u->ch[i]);
                else
                    u->ch[i] = u->f->ch[i];
            }
        }
    }
    void query(const char *s) {
        memset(cnt, 0, sizeof(cnt));
        Node *u = rt;
        for (int i = 0, c; s[i]; i++) {
            c = idx(s[i]);
            u = u->ch[c];
            for (auto p = u; p != rt; p = p->f) {
                cnt[p->val]++;
            }
        }
    }
    void delTrie() {
        for (auto &v : nodes) delete v;
        nodes.clear();
    }
} trie;

int main() {
//	/*
#ifndef ONLINE_JUDGE
    freopen("1.in", "r", stdin);
    freopen("1.out", "w", stdout);
#endif
    //	*/
    std::ios::sync_with_stdio(false);
    int n;
    while (~scanf("%d", &n)) {
        trie.init();
        for (int i = 1; i <= n; i++) {
            scanf("%s", pat[i]);
            trie.insert(i, pat[i]);
        }
        trie.build();
        scanf("%s", t);
        trie.query(t);
        for (int i = 1; i <= n; i++)
            if (cnt[i]) printf("%s: %d\n", pat[i], cnt[i]);
        trie.delTrie();
    }
}