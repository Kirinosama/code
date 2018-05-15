#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

#define MAXN 100010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int cnt[MAXN],a[MAXN];
int n,c,m,sqr,ans[MAXN],now;

struct query{
    int l,r,ID;
    bool operator < (const query &a)const{
        if(l/sqr==a.l/sqr) return r<a.r;
        return l/sqr<a.l/sqr;
    }
}q[MAXN];

void update(int x,int k){
    if(cnt[x]){
        if(cnt[x]==1 && k==-1);
        else if(cnt[x]&1) now++;
        else now--;
    }
    cnt[x]+=k;
}

int main(){
    freopen("harem.in","r",stdin);
    freopen("harem.out","w",stdout);
    cin>>n>>c>>m;sqr=(int)sqrt(n);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    for(int i=1;i<=m;i++)scanf("%d%d",&q[i].l,&q[i].r),q[i].ID=i;
    sort(q+1,q+m+1);
    int l=1,r=1;cnt[a[1]]=1;
    for(int i=1;i<=m;i++){
        while(l>q[i].l) l--,update(a[l],1);
        while(r<q[i].r) r++,update(a[r],1);
        while(l<q[i].l) update(a[l],-1),l++;
        while(r>q[i].r) update(a[r],-1),r--;
        ans[q[i].ID]=now;
    }
    for(int i=1;i<=m;i++)printf("%d\n",ans[i]);
    return 0;
}
