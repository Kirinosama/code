#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <cmath>
using namespace std;

#define MAXN 40010

int n,m,a[MAXN],book[MAXN],dif[MAXN],f[MAXN],b[MAXN],ne[MAXN],last[MAXN];

int main()
{
	freopen("input","r",stdin);
	scanf("%d %d",&n,&m);
	dif[0]=-1;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		if(!book[a[i]])
		{
			book[a[i]]=1;
			dif[i]=dif[i-1]+1;
		}
		else dif[i]=dif[i-1];
	}
	m=floor(sqrt(n));
	for(int i=1;i<=m;i++) b[i]=1;
	for(int i=1;i<=n;i++)
	{
		ne[i]=last[a[i]];
		last[a[i]]=i;
		for(int j=1;j<=min(m,dif[i]);j++)
		{
			if (b[j]>ne[i])
			{
                while (1)
                {
                    b[j]++;
                    if (b[j]-1==last[a[b[j]-1]]) break;
                }
            }
		}
		f[i]=i;
		for(int j=1;j<=min(m,dif[i]);j++)
			f[i]=min(f[b[j]-1]+j*j,f[i]);
	}
	cout<<f[n];
	return 0;
}