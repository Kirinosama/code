#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;
int n,m,a[60][60];
ll heng[60][2],shu[60][2],c[100][100],ans;

int main()
{
	freopen("input","r",stdin);
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			scanf("%d",&a[i][j]);
			heng[i][a[i][j]]++;
			shu[j][a[i][j]]++;
		}
	c[0][0]=1;
	for(int i=1;i<=60;i++)
	{
		c[i][0]=1;
		for(int j=1;j<=i;j++)
		{
			c[i][j]=c[i-1][j-1]+c[i-1][j];
		}
	}
	ans+=n*m;
	for(int i=1;i<=n;i++)
		for(int j=2;j<=m;j++)
			ans+=c[heng[i][0]][j]+c[heng[i][1]][j];
	for(int i=1;i<=m;i++)
		for(int j=2;j<=n;j++)
			ans+=c[shu[i][0]][j]+c[shu[i][1]][j];
	cout<<ans;
	return 0;
}