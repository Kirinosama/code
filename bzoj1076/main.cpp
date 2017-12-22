#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
typedef long long ll;
const int mod=1e9+7;
int sum[6],n;
ll f[16][16][16][16][16][16];

ll dfs(int a,int b,int c,int d,int e,int last)
{
	if (a+b+c+d+e==0) return f[a][b][c][d][e][last]=1;
	if (f[a][b][c][d][e][last]!=-1) return f[a][b][c][d][e][last];
	
	ll t=0;
	if (a>0) t+=(a-(last==2))*dfs(a-1,b,c,d,e,1),t%=mod;
	if (b>0) t+=(b-(last==3))*dfs(a+1,b-1,c,d,e,2),t%=mod;
	if (c>0) t+=(c-(last==4))*dfs(a,b+1,c-1,d,e,3),t%=mod;
	if (d>0) t+=(d-(last==5))*dfs(a,b,c+1,d-1,e,4),t%=mod;
	if (e>0) t+=e*dfs(a,b,c,d+1,e-1,5),t%=mod;
	f[a][b][c][d][e][last]=t;
	return t; 
}

int main()
{
	scanf("%d",&n);
	int x;
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&x);
		sum[x]++;
	}
	memset(f,-1,sizeof(f));
	printf("%lld",dfs(sum[1],sum[2],sum[3],sum[4],sum[5],0));
	return 0;
}
