#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <vector>
#include <cmath>
using namespace std;

const double eps=1e-8;
const int INF=0x3f3f3f3f;

int n,a[110],f[110][2];

int main()
{
	freopen("input","r",stdin);
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	f[0][0]=1;
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<i;j++)
		{
			if(a[j+1]%2==1 && a[i]%2==1 && (i-j)%2==1)
			{
				if(f[j][0]) f[i][1]=1;
				if(f[j][1]) f[i][0]=1;
			}
		}
	}
	if(f[n][1]) printf("Yes");
	else printf("No");
	return 0;
}
