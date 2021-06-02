#include <bits/stdc++.h>
#define lson (rt << 1)
#define rson (rt << 1 | 1)
using namespace std;
const int maxn = 1e5 + 5;
int a[maxn], type[maxn], b[maxn];
map<int, int> val,rval;
struct Node {
  int cnt;
  long long sum[5];
} seg[maxn << 2];

void build(int l,int r,int rt){
  seg[rt].cnt = 0;
  for(int i=0;i<5;i++) seg[rt].sum[i] = 0;
  if(l == r) return;
  int m = l + r >> 1;
  build(l,m,lson);
  build(m+1,r,rson);
}
void pushup(int rt){
  seg[rt].cnt = seg[lson].cnt + seg[rson].cnt;
  for(int i=0;i<5;i++)
    seg[rt].sum[i] = seg[lson].sum[i] + seg[rson].sum[(i + seg[lson].cnt) % 5];
}
void update(int l,int r,int rt,int p,int x){
  if(l == r){
    seg[rt].cnt += x;
    seg[rt].sum[0]+= x * rval[l];
    return ;
  }
  int m = l + r >> 1;
  if(p <= m) update(l,m,lson,p,x);
  else update(m+1,r,rson,p,x);
  pushup(rt);
}
int main() {
  char op[10];
  int n;
  while (~scanf("%d", &n)) {
    int tot = 0;
    for (int i = 0, x; i < n; i++) {
      scanf("%s", op);
      if (op[0] == 'a' || op[0] == 'd') {
        scanf("%d", a + i);
        type[i] = op[0] == 'a';
        if (op[0] == 'a') b[tot++] = a[i];
      } else {
        a[i] = -1;
      }
    }
    sort(b, b + tot);
    int sz = unique(b, b + tot) - b;
    val.clear();
    rval.clear();
    for (int i = 0; i < n; i++) {
      if (a[i] != -1) {
        int tmp = lower_bound(b, b + sz, a[i]) - b + 1;
        val[a[i]] = tmp;
        rval[tmp] = a[i];
      }
    }
    build(1,n,1);
    for (int i = 0; i < n; i++) {
      if(a[i] == -1)
        printf("%lld\n",seg[1].sum[3]);
      else{
        if(type[i] == 0){
          update(1,n,1,val[a[i]],-1);
        } else{
          update(1,n,1,val[a[i]],1);
        }
      }
    }
  }
}