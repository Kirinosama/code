#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int T,n,m,a[40][40],f[40][40][1810];

void solve(){
	cin>>n>>m;int ans=INF;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%d",&a[i][j]);
	memset(f,0x3f,sizeof(f));
	f[1][1][a[1][1]]=a[1][1]*a[1][1];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			for(int k=a[i][j];k<=30*(i+j-1);k++){
			if(i-1>=1)f[i][j][k]=min(f[i][j][k],f[i-1][j][k-a[i][j]]+a[i][j]*a[i][j]);
			if(j-1>=1)f[i][j][k]=min(f[i][j][k],f[i][j-1][k-a[i][j]]+a[i][j]*a[i][j]);
		}
	for(int i=n+m-1;i<=30*(n+m-1);i++)if(f[n][m][i]!=INF)
		ans=min(ans,(n+m-1)*f[n][m][i]-i*i);
	printf("%d\n",ans);
}

int main(){
    freopen("matrix10.in","r",stdin);
    cin>>T;
    while(T--) solve();
    return 0;
}