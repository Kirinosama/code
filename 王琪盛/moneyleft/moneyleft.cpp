#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 210

typedef long long ll;

ll f[MAXN][MAXN];
ll a[MAXN][MAXN];
ll ans,n,m;

int main(){
	freopen("moneyleft.in","r",stdin);
	freopen("moneyleft.ans","w",stdout);
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%lld",&a[i][j]);
	for(int i=1;i<=n+1;i++)
		for(int j=1;j<=m;j++)
			f[i][j]=-1e18;
	f[n+1][(m+1)/2]=0;
	for(int i=n;i>=1;i--){
		for(int j=1;j<=m;j++)
			for(int k=-2;k<=2;k++){
				if(j+k<1 || j+k>m) continue;
				if(f[i+1][j+k]==-1e18) continue;
				f[i][j]=max(f[i][j],f[i+1][j+k]+a[i][j]);
			}
	}
	ans=-1e18;
	for(int i=1;i<=m;i++) ans=max(ans,f[1][i]);
	cout<<ans;
	return 0;
}