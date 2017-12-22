#include <cstdlib>
#include <cstdio>
#include <iostream>


#define MAXN 2000010

int a[MAXN],b[MAXN],n,m,k,ans;
int father[MAXN];

void init()
{
	for(int i=1;i<=n;i++)
		father[i]=i;
}

int find(int x)
{
	if(father[x]!=x)
		father[x]=find(father[x]);
	return father[x];
}

void merge(int x,int y)
{
	int fx=find(x);
	int fy=find(y);
	if(fx!=fy)
		father[fx]=fy;
}

int main()
{
	freopen("input","r",stdin);
	scanf("%d %d %d",&n,&m,&k);
	init();
	for(int i=1;i<=m;i++)
	{
		scanf("%d %d",&a[i],&b[i]);
		{
			if(a[i]>b[i])
				std::swap(a[i],b[i]);
			if(a[i]>k && b[i]>k)
			{
				merge(a[i],b[i]);
				a[i]=0;b[i]=0;
			}
		}
	}
	for(int i=1;i<=m;i++)
	{
		if(a[i] && b[i] && find(a[i])!=find(b[i]))
		{
			merge(a[i],b[i]);
			a[i]=b[i]=0;
		}
		else if(a[i] && b[i])
			ans++;
	}
	printf("%d\n",ans);
	for(int i=1;i<=m;i++)
		if(a[i] && b[i])
			printf("%d %d\n",a[i],b[i]);
	return 0;
}