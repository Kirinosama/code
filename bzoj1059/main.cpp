#include <cstdlib>
#include <cstdio>
#include <queue>
#include <cstring>
#include <iostream>
using namespace std;

#define INF 0x3f3f3f3f
#define MAXN 410
#define next_edge(x) (x%2?x+1:x-1)

struct node
{
	int from,to;
	int w;
}E[MAXN*MAXN];

int edge_cnt,head[MAXN],ne[MAXN*MAXN];
int n,m,s,t,dis[MAXN];
int a[MAXN][MAXN];

void init()
{
	edge_cnt=0;
	memset(head,0,sizeof(head));
}

void insert(int u,int v,int k)
{
	E[++edge_cnt].from=u;
	E[edge_cnt].to=v;
	E[edge_cnt].w=k;
	ne[edge_cnt]=head[u];
	head[u]=edge_cnt;
}

int bfs()
{
	memset(dis,-1,sizeof(dis));
	queue <int> Q;
	Q.push(s);
	dis[s]=0;
	while(!Q.empty())
	{
		int u=Q.front();
		for(int i=head[u];i;i=ne[i])
		{
			int v=E[i].to;
			if(dis[v]==-1 && E[i].w>0)
			{
				dis[v]=dis[u]+1;
				Q.push(v);
			}
		}
		Q.pop();
	}
	if(dis[t]==-1) return 0;
	return 1;
}

int dinic(int x,int flow)
{
	int p=0;
	if(x==t) return flow;
	for(int i=head[x];i;i=ne[i])
	{
		int v=E[i].to;
		if(dis[v]==dis[x]+1 && (p=dinic(v,min(flow,E[i].w))))
		{
			E[i].w-=p;
			E[next_edge(i)].w+=p;
			return p;
		}
	}
	return 0;
}

void solve()
{
	int res=0;
	init();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			scanf("%d",&a[i][j]);
			if(a[i][j])
			{
				insert(i,j+n,1);
				insert(j+n,i,0);
			}
		}

	s=2*n+1;t=2*n+2;

	for(int i=1;i<=n;i++)
	{
		insert(s,i,1);
		insert(i,s,0);
	}
	for(int i=n+1;i<=2*n;i++)
	{
		insert(i,t,1);
		insert(t,i,0);
	}
	while(bfs())
	{
		while(int tans=dinic(s,INF))
			res+=tans;
	}
	if(res==n) printf("Yes\n");
	else printf("No\n");
}

int main()
{
	freopen("input","r",stdin);
	scanf("%d",&m);
	while(m--)
	{
		scanf("%d",&n);
		solve();
	}
	return 0;
}
