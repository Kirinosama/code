#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 100010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int n,casecnt;
ll C,D,f[MAXN],d[MAXN],p[MAXN],r[MAXN],g[MAXN];

void solve(int L,int R){
    if(L==R) return;
    int mid=(L+R)>>1;
    solve(L,mid);
    for(int i=mid+1;i<=R;i++){
        for(int j=L;j<=mid;j++)if(f[j]>=0){
            ll res=f[j]+(d[i]-d[j]-1)*g[j];
            if(res<p[i]) continue;
            else f[i]=max(f[i],res-p[i]+r[i]);
        }
    }
    solve(mid+1,R);
}

int main(){
    freopen("bzoj3963.in","r",stdin);
    while(1){
        cin>>n>>C>>D;
        if(!n && !C && !D) break;
        casecnt++;
        for(int i=1;i<=n;i++)scanf("%lld%lld%lld%lld",&d[i],&p[i],&r[i],&g[i]);
        memset(f,-1,sizeof(f));f[0]=C;d[0]=0;g[0]=0;
        solve(0,n);ll ans=0;
        for(int i=0;i<=n;i++)if(f[i]>=0){
            ans=max(ans,(D-d[i])*g[i]+f[i]);
            cout<<i<<' '<<ans<<endl;
        }
        printf("Case %d: %lld\n",casecnt,ans);
    }
    return 0;
}
