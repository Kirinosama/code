#include <cstdlib>
#include <cstdio>
#include <cstring>
using namespace std;

#define MAXN 510
const int MOD=1024523;

char a[MAXN],b[MAXN];
int f[MAXN][MAXN][MAXN];
int n,m;

int main()
{
	freopen("input","r",stdin);
	scanf("%d %d\n",&n,&m);
	for(int i=1;i<=n;i++)scanf("%c",&a[i]);
		scanf("\n");
	for(int i=1;i<=m;i++)scanf("%c",&b[i]);
	f[0][0][0]=1;
	for(int i=0;i<=n;i++)
		for(int j=0;j<=m;j++)
			for(int k=0;k<=n;k++)
			{
				int t=i+j-k;
				if(t>m || t<0) continue;
				if(a[i]==a[k] && i && k)
				{
					f[i][j][k]+=f[i-1][j][k-1];
					if(f[i][j][k]>=MOD) f[i][j][k]-=MOD;
				}
				if(a[i]==b[t] && i && t)
				{
					f[i][j][k]+=f[i-1][j][k];
					if(f[i][j][k]>=MOD) f[i][j][k]-=MOD;
				}
				if(b[j]==a[k] && j && k)
				{
					f[i][j][k]+=f[i][j-1][k-1];
					if(f[i][j][k]>=MOD) f[i][j][k]-=MOD;
				}
				if(b[j]==b[t] && j && t)
				{
					f[i][j][k]+=f[i][j-1][k];
					if(f[i][j][k]>=MOD) f[i][j][k]-=MOD;
				}
			}
	printf("%d",f[n][m][n]);
	return 0;
}