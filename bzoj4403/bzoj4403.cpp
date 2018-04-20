#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 1000010
#define MOD 1000003
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

ll fac[MAXN],inv[MAXN];
int T;

ll cal(int x,int y){
   return ((fac[x]*inv[fac[x-y]])%MOD*inv[fac[y]])%MOD;
}

ll c(int x,int y){
    if(x<y) return 0;
    if(!y) return 1;
    if(x<MOD && y<MOD) return cal(x,y);
    return (c(x/MOD,y/MOD)*c(x%MOD,y%MOD))%MOD;
}

void premake(){
    fac[0]=fac[1]=1;inv[0]=inv[1]=1;
    for(int i=2;i<=MOD;i++)fac[i]=(fac[i-1]*i)%MOD;
    for(int i=2;i<=MOD;i++)inv[i]=(inv[MOD%i]*(MOD-MOD/i))%MOD;
}

int main(){
    freopen("bzoj4403.in","r",stdin);
    cin>>T;premake();
    while(T--){
        int n,l,r;scanf("%d%d%d",&n,&l,&r);
        printf("%lld\n",(c(n+r-l+1,r-l+1)-1+MOD)%MOD);
    }
    return 0;
}
