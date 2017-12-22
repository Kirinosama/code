#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;

#define MAXN 1024
#define MAXM 20010
#define INF 0x3f3f3f3f

struct edge
{
	int from,to,f;
}E[MAXM];

int go[4][2]={{0,1},{0,-1},{-1,0},{1,0}};
int edge_cnt,last[MAXN],ne[MAXM],n,cor[33][33],a[33][33];
int ans,cur[MAXN],dis[MAXN],s,t,res;

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

int bfs()
{
	queue <int> Q;
	memset(dis,-1,sizeof(dis));
	dis[s]=0;Q.push(s);
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
			tmp=dinic(v,min(E[i].f,f-sum));
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
	scanf("%d",&n);
	edge_cnt=1;cor[1][1]=1;s=n*n+1;t=s+1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			scanf("%d",&a[i][j]);res+=a[i][j];
			cor[i+1][j]=cor[i][j+1]=cor[i][j]^1;
			if(cor[i][j]) add(s,(i-1)*n+j,a[i][j]);
			else add((i-1)*n+j,t,a[i][j]);
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			if(cor[i][j])
			{
				for(int k=0;k<4;k++)
				{
					int tx=i+go[k][0];
					int ty=j+go[k][1];
					if(tx<1 || tx>n || ty<1 || ty>n) continue;
					add((i-1)*n+j,(tx-1)*n+ty,INF);
				}
			}
		}
	while(bfs())
	{
		for(int i=1;i<=t;i++) cur[i]=last[i];
			ans+=dinic(s,INF);
	}
	cout<<res-ans;
	return 0;
}