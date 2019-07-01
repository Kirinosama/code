#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<time.h>
#include<vector>
#define M 511100
#define inf 99999999
using namespace std;
struct edge{
	int next;
	int from;
	int to;
	int v;
}e[M];
int m,n,dis[M],cnt,head[M],flag[M];
void add(int f,int t,int va)
{
	e[++cnt].next=head[f];
	e[cnt].from=f;
	e[cnt].v=va;
	e[cnt].to=t;
	head[f]=cnt;
}
int main()
{
	freopen("input","r",stdin);
	freopen("output","w",stdout);
	int t;
	scanf("%d",&t);
	for (int b=1;b<=t;b++)
	{
		memset(head,0,sizeof(head));
		memset(flag,0,sizeof(flag));
		cnt=0;
	scanf("%d %d",&n,&m);
	int tmp=m;
	for (int i=1;i<=m;i++)
	{
		int x,y,disss;
		scanf("%d %d %d",&x,&y,&disss);
		if (disss>=0)
		{
			add(y,x,disss);
			tmp++;
		}
		add(x,y,disss);
	}
	for (int i=1;i<=n;i++)
	{
		dis[i]=inf;
	}
	dis[1]=0;flag[1]=1;
	for (int i=1;i<n;i++)
	{
		for (int j=1;j<=tmp;j++)
		{
			if(flag[e[j].from]) flag[e[j].to]=1;
			dis[e[j].to]=min(dis[e[j].to],dis[e[j].from]+e[j].v);
		}
	}
	int ans=0;
	for (int j=1;j<=tmp;j++)
	{
		if (dis[e[j].to]>dis[e[j].from]+e[j].v && (flag[e[j].to] || flag[e[j].from]))
		{
			ans=1;
			break;
		}
	}
	if (ans)
	{
		printf("YE5\n");
	}
	else
	{
		printf("N0\n");
	}
	}
	return 0;
}
