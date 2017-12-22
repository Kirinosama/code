#include <cstdlib>
#include <cstdio>
#include <iostream>
using namespace std;

#define MAXN 10010
#define MAXW 110
#define MOD 1000000007

int w,n,h,f[MAXW][MAXN],pre[MAXN];
int ans;

int main()
{
	freopen("input","r",stdin);
	scanf("%d %d %d",&n,&w,&h);
	f[0][0]=1;
	for(int i=1;i<=w;i++)
		for(int j=0;j<=min(i*h,n);j++)
			for(int k=max(j-h,0);k<=j;k++)
			{
				f[i][j]+=f[i-1][k];
				if(f[i][j]>=MOD)
					f[i][j]-=MOD;
			}

	//for(int i=1;i<=w;i++)
	//	for(int j=0;j<=n;j++)
	//		printf("f[%d][%d]:%d\n",i,j,f[i][j]);

	int minus=n/w+1;

	for(int i=0;i<=n;i++)
	{
		ans+=f[w][i];
		if(ans>=MOD)
			ans-=MOD;
	}

	ans+=MOD;
	printf("%d",(ans-minus)%MOD);
}

