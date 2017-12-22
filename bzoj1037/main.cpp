#include <cstdlib>
#include <cstdio>
#include <iostream>
using namespace std;

int n,m,k,ans;
int f[310][160][22][22];
const int MOD=12345678;

int main()
{
	freopen("input","r",stdin);
	scanf("%d %d %d",&n,&m,&k);
	f[0][0][0][0]=1;
	for(int i=0;i<n+m;i++)
		for(int p=0;p<=n;p++)
			for(int j=0;j<=k;j++)
				for(int t=0;t<=k;t++)
				{
					if(j+1<=k && p+1<=n)
						f[i+1][p+1][j+1][max(t-1,0)]=(f[i+1][p+1][j+1][max(t-1,0)]+f[i][p][j][t])%MOD;
					if(t+1<=k && i-p+1<=m)
						f[i+1][p][max(j-1,0)][t+1]=(f[i+1][p][max(j-1,0)][t+1]+f[i][p][j][t])%MOD;
				}
	for(int i=0;i<=k;i++)
		for(int j=0;j<=k;j++)
			ans=(ans+f[n+m][n][i][j])%MOD;
	printf("%d",ans);
	return 0;
}