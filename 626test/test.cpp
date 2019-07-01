#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<vector>
#include<stack> 
#define M 101000
using namespace std;
int t,q,cnt,to[M],ne[M],head[M],dep[M],n,m,f[M][30],c[M]; 
void add(int a,int b)
{
	cnt++;
	to[cnt]=b;
	ne[cnt]=head[a];
	head[a]=cnt;
}
void init(int u,int father)
{
	dep[u]=dep[father]+1;
	for (int ii=0;ii<=20;ii++)
	{
		f[u][ii+1]=f[f[u][ii]][ii]; 
	}
	for (int ii=head[u];ii;ii=ne[ii])
	{
		int e=to[ii];
		if (e==father)
		{
			continue;
		}
		f[e][0]=u;
		init(e,u);
	} 
}
int lca(int x,int y)
{
	if (dep[x]<dep[y])
	{
		swap(x,y);
	}
	for (int ii=20;ii>=0;ii--)
	{
		if (dep[f[x][ii]]>=dep[y])
		{
			x=f[x][ii];
		}
		if (x==y)
		{
			return x;
		}
	}
	for (int ii=20;ii>=0;ii--)
	{
		if (f[x][ii]!=f[y][ii])
		{
			x=f[x][ii];
			y=f[y][ii];
		}
	} 
	return f[x][0];
}
int main()
{
	scanf("%d",&t);
	for (int i=1;i<=t;i++)
	{
		cnt=0;
		memset(head,0,sizeof(head));
		memset(to,0,sizeof(to));
		memset(ne,0,sizeof(ne));
		memset(dep,0,sizeof(dep));
		memset(c,0,sizeof(c));
		memset(f,0,sizeof(f)); 
		scanf("%d",&n);
		for (int j=1;j<=n;j++)
		{
			scanf("%d",&m);
			for (int k=1;k<=m;k++)
			{
				int x;
				scanf("%d",&x);
				add(j,x);
				c[x]++;
			}
		}
		int root;
		for (int j=1;j<=n;j++)
		{
			if (!c[j])
			{
				root=j;
			}
		}
		init(root,0);
		scanf("%d",&q);
		printf("Case %d:\n",i);
		for (int j=1;j<=q;j++)
		{
			int u,v;
			scanf("%d %d",&u,&v);
			printf("%d\n",lca(u,v));
		}
	} 
	return 0;
} 
