#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

#define MOD 1000000000
typedef long long ll;
int n,m,a[10][10],num[10][10],cnt;
ll A[100][100],B[100][100];
int go[2][2]={{0,1},{1,0}};


void premake(){
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++){
            if(!a[i][j]) continue;
            int now=num[i][j],to;
            for(int k=0;k<2;k++){
                int tx=i+go[k][0];
                int ty=j+go[k][1];
                if(tx<1 || tx>n || ty<1 || ty>m || a[tx][ty]==0) continue;
                to=num[tx][ty];A[now][now]++,A[to][to]++,B[to][now]=B[now][to]=1;
            }
        }
    n=cnt-1; 
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            A[i][j]=(A[i][j]-B[i][j]+MOD)%MOD;
}

ll solve(){
    ll ans=1,f=1;
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            ll x=A[i][i],y=A[j][i];
            while(y){
                ll t=x/y;x%=y,swap(x,y);
                for(int k=i;k<=n;k++) A[i][k]=((A[i][k]-A[j][k]*t)%MOD+MOD)%MOD;
                for(int k=i;k<=n;k++) swap(A[i][k],A[j][k]);
                f=-f;
            }
        }
        if(!A[i][i]) return 0;
        ans=(ans*A[i][i])%MOD;
    }
    if(f==1) return ans%MOD;
    else return (2*MOD-ans)%MOD;
}

int main(){
    freopen("bzoj4031.in","r",stdin);
    cin>>n>>m;char c;
    for(int i=1;i<=n;i++){
        getchar();
        for(int j=1;j<=m;j++){
            scanf("%c",&c),a[i][j]=(c=='.');
            if(a[i][j]) num[i][j]=++cnt;
        }
    }
    premake();
    printf("%lld\n",solve());
    return 0;
}
