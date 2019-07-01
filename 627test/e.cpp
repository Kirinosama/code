#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<time.h>
#define M 2010000
#define inf 0x3f3f3f3f
#define LL long long
using namespace std;
LL fa[M],n,m,minans,ans,cnt,cnte,head[M],used[M],dep[M],w2[M][30],w1[M][30],f[M][30];
LL find(LL a)
{
	if (fa[a]!=a)
	{
		return find(fa[a]);
	}
	return a;
}
struct Edge
{
	LL to,from,value,next;
}edge[M];
void add(LL u,LL v,LL dis)
{
	edge[++cnte].next=head[u];
	edge[cnte].from=u;
	edge[cnte].to=v;
	edge[cnte].value=dis;
	head[u]=cnte;
}
LL cmp(Edge a,Edge b)
{
	return a.value<b.value;
}
void kruskal()
{
	sort(edge+1,edge+m+1,cmp);
	for (LL i=1;i<=m;i++)
	{
		LL x=find(edge[i].from);
		LL y=find(edge[i].to);
		if (x==y)
		{
			continue;
		}
		ans+=edge[i].value;
		used[i]=1;
		fa[y]=x;
		cnt++;
		if (cnt==n-1)
		{
			return; 
		}
	}
}
void init(LL u,LL father)
{
	dep[u]=dep[father]+1;
	f[u][0]=father;
	for (LL ii=0;ii<=20;ii++)
	{
		f[u][ii+1]=f[f[u][ii]][ii]; 
		w1[u][ii+1]=max(w1[u][ii],w1[f[u][ii]][ii]);
		w2[u][ii+1]=max(w2[u][ii],w2[f[u][ii]][ii]);
		if (w1[u][ii]>w1[f[u][ii]][ii])
		{
			w2[u][ii+1]=max(w2[u][ii+1],w1[f[u][ii]][ii]);
		}
		if (w1[u][ii]<w1[f[u][ii]][ii])
		{
			w2[u][ii+1]=max(w2[u][ii+1],w1[u][ii]);
		}
	}
	for (LL ii=head[u];ii;ii=edge[ii].next)
	{
		LL e=edge[ii].to;
		if (e==father)
		{
			continue;
		}
		w1[e][0]=edge[ii].value;
		f[e][0]=u;
		init(e,u);
	} 
}
LL lca(LL x,LL y)
{
	if (dep[x]<dep[y])
	{
		swap(x,y);
	}
	for (LL ii=20;ii>=0;ii--)
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
	for (LL ii=20;ii>=0;ii--)
	{
		if (f[x][ii]!=f[y][ii])
		{
			x=f[x][ii];
			y=f[y][ii];
		}
	} 
	return f[x][0];
}
LL query (LL x,LL y,LL d)
{
	LL anst=-1;
	for (LL i=20;i>=0;i--)
	{
		if (dep[f[x][i]]>=dep[y])
		{
			if (d!=w1[x][i])
			{
				anst=max(anst,w1[x][i]);
			}
			else
			{
				anst=max(anst,w2[x][i]);
			}
			x=f[x][i];
		}
	}
	return anst;
}
int main()
{
	freopen("input","r",stdin);
	scanf("%d %d",&n,&m);
	for (LL i=1;i<=n;i++)
	{
		fa[i]=i;
		w2[i][0]=-1;
	}
	for (LL i=1;i<=m;i++)
	{
		LL x,y,z;
		scanf("%d %d %d",&x,&y,&z);
		add(x,y,z);
		add(y,x,z); 
	}
	kruskal();
	init(1,0);
	for (LL i=1;i<=m;i++)
	{
		if (!used[i])
		{
			LL LCA=lca(edge[i].from,edge[i].to);
			LL maxu=query(edge[i].from,LCA,edge[i].value);
			LL maxv=query(edge[i].to,LCA,edge[i].value);
			minans=min(minans,ans-max(maxu,maxv)+edge[i].value);
		}
	}
	printf("%d",minans);
	return 0;
}
