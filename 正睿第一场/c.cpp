#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 20010

const int INF=0x7fffffff;
int a[MAXN],n;
int f[1010][1010],ans[MAXN];

void solve1()
{
	memset(ans,0x80,sizeof(ans));
	memset(f,0x80,sizeof(f));
	f[0][0]=0;
	for(int i=1;i<=n;i++)
		for(int j=i;j<=n;j++)
			for(int k=i-1;k<j;k++)
			{
				if(i%2) f[i][j]=max(f[i][j],f[i-1][k]+a[j]);
				else f[i][j]=max(f[i][j],f[i-1][k]-a[j]);
				ans[i]=max(ans[i],f[i][j]);
			}
	for(int i=1;i<=n;i++) printf("%d ",ans[i]);
}

int main()
{
	freopen("input","r",stdin);
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	if(n<=1000)
		 solve1();
	return 0;
}