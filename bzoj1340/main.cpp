#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <cmath>
#include <queue>
using namespace std;

typedef long long ll;
#define MAXN 600
#define MAXM 720010
const int INF=1e9;

struct edge
{
	int from,to,f;
}E[MAXM];

struct node
{
	int x,y;
}p[MAXN];

int last[MAXN],ne[MAXM],edge_cnt,ans,n,m,w,s,t,dis[MAXN],cur[MAXN];

void insert(int x,int y,int f)
{
	E[++edge_cnt].from=x;
	E[edge_cnt].to=y;
	E[edge_cnt].f=f;
	ne[edge_cnt]=last[x];
	last[x]=edge_cnt;
}

void add(int x,int y,int f)
{
	insert(x,y,f);
	insert(y,x,0);
}

ll sqr(int x)
{
	return 1ll*x*x;
}

int bfs()
{
	queue <int> Q;
	memset(dis,-1,sizeof(dis));
	Q.push(s);dis[s]=0;
	while(!Q.empty())
	{
		int tp=Q.front();Q.pop();
		if(tp==t) return 1;
		for(int i=last[tp];i;i=ne[i])
		{
			int v=E[i].to;
			if(dis[v]==-1 && E[i].f)
			{
				dis[v]=dis[tp]+1;
				Q.push(v);
			}
		}
	}
	return 0;
}

int dinic(int x,int f)
{
	int sum=0,tmp;
	if(x==t) return f;
	for(int &i=cur[x];i;i=ne[i])
	{
		int v=E[i].to;
		if(dis[v]==dis[x]+1 && E[i].f)
		{
			tmp=dinic(v,min(f-sum,E[i].f));
			sum+=tmp;E[i].f-=tmp;E[i^1].f+=tmp;
			if(sum==f) return sum;
		}
	}
	if(!sum) dis[x]=-1;
	return sum;
}

int main()
{
	freopen("input","r",stdin);
	scanf("%d %d %d",&n,&m,&w);
	s=2*w+1;t=s+1;edge_cnt=1;
	for(int i=1;i<=w;i++)
	{
		scanf("%d %d",&p[i].x,&p[i].y);
		if(p[i].y<=100) add(s,i,INF);
		if(p[i].y+100>=m) add(i+w,t,INF);
		add(i,i+w,1);
	}
	for(int i=1;i<=w;i++)
		for(int j=1;j<=w;j++)
		{
			if(i!=j && sqr(p[i].x-p[j].x)+sqr(p[i].y-p[j].y)<=40000)
				add(i+w,j,INF);
		}
	while(bfs())
	{
		for(int i=1;i<=t;i++) cur[i]=last[i];
			ans+=dinic(s,INF);
	}
	cout<<ans;
	return 0;
}