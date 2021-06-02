#include<cstdio>
#include<set>
#include<deque>

using namespace std;
const int INF = 0x3f3f3f3f;
const int maxn = 1e6+6;
typedef pair<int,int> pii;
int f[maxn],dp[maxn];

int main(){
    int n,l,a,b;
    scanf("%d%d%d%d",&n,&l,&a,&b);
    for(int i=0;i<=l;i++) f[i] = 0;
    for(int i=0,x,y;i<n;i++){
        scanf("%d%d",&x,&y);
        f[x+1]++;
        f[y]--;
    }
    for(int i=1;i<=l;i++) f[i] += f[i-1];
    dp[0] = 0;
    for(int i=1;i<=l;i++) dp[i] = INF;
    deque<pii> dq;
    a <<= 1;
    b <<= 1;
    for(int i=a;i<=l;i+=2){
        while(dq.size() && dq.back().first >= dp[i-a]) dq.pop_back();
        dq.push_back(make_pair(dp[i-a],i-a));
        if(f[i] == 0) dp[i] = dq.front().first + 1;
        while(i >= b && dq.size() && i - dq.front().second >= b) dq.pop_front();
    }
    printf("%d\n", dp[l] >= INF ? -1 : dp[l]);
}
/*
2 8
1 2
6 7
3 6
 */