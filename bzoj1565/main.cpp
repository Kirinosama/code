#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>
using namespace std;

#define ii pair<int,int>
#define MAXN 1010
#define MAXM 1000010
#define INF 0x7fffffff

int v[MAXN],x,p,q,n,m,ru[MAXN];
int book[MAXN],edge_cnt,last[MAXN],ne[MAXM];
int edge_cnt1,last1[MAXN],ne1[MAXM];
int ans,dis[MAXN],cur[MAXN],s,t;

struct edge
{
	int from,to,k;
}E[MAXM];

edge E1[MAXM];

int num(int x,int y)
{
	return (x*m+y+1);
}

void add(int x,int y,int k)
{
	E1[++edge_cnt1].from=x;
	E1[edge_cnt1].to=y;
	E1[edge_cnt1].k=k;
	ne1[edge_cnt1]=last1[x];
	last1[x]=edge_cnt1;
}

void paint(int x)
{
	book[x]=0;
	for(int i=last[x];i;i=ne[i])
	{
		int v=E[i].to;
		if(book[v]==1) paint(v);
	}
}

void make()
{
	priority_queue <ii,vector<ii>,greater<ii> > Q;
	for(int i=1;i<=num(n-1,m-1);i++)
		Q.push(make_pair(ru[i],i));
	while(Q.top().first==0)
	{
		int tp=Q.top().second;Q.pop();
		if(!book[tp])
		{
			book[tp]=1;
			for(int i=last[tp];i;i=ne[i])
			{
				int v=E[i].to;
				if(ru[v]>0)
				{
					ru[v]--;
					Q.push(make_pair(ru[v],v));
				}
			}
		}
	}
	s=num(n-1,m-1)+1;t=s+1;
	for(int i=1;i<=t;i++) 
		if(!book[i])
			paint(i);
	book[s]=book[t]=1;
	for(int i=1;i<=edge_cnt;i++)
		if(book[E[i].from] && book[E[i].to])
		{
			add(E[i].from,E[i].to,0);
			add(E[i].to,E[i].from,INF);
		}
	for(int i=1;i<=num(n-1,m-1);i++)
	{
		if(book[i])
		{
			if(v[i]>0) {add(s,i,v[i]);add(i,s,0);ans+=v[i];}
			if(v[i]<0) {add(i,t,-v[i]);add(t,i,0);}
		}
	}
}

int bfs()
{
	queue<int> q;
	memset(dis,-1,sizeof(dis));
	dis[s]=0;q.push(s);
	while(!q.empty())
	{
		int tp=q.front();q.pop();
		if(tp==t) return 1;
		for(int i=last1[tp];i;i=ne1[i])
		{
			int v=E1[i].to;
			if(E1[i].k && dis[v]==-1)
			{
				dis[v]=dis[tp]+1;
				q.push(v);
			}
		}
	}
	return 0;
}

int dinic(int x,int f)
{
	int sum=0;
	if(x==t) return f;
	for(int &i=cur[x];i;i=ne1[i])
	{
		int v=E1[i].to;
		if(dis[v]==dis[x]+1 && E1[i].k)
		{
			int res=dinic(v,min(f-sum,E1[i].k));
			E1[i].k-=res;E1[i^1].k+=res;sum+=res;
			if(sum==f) return sum;
		}
	}
	if(sum==0) dis[x]=-1;
	return sum;
}

int main()
{
	freopen("input","r",stdin);
	scanf("%d %d",&n,&m);
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			scanf("%d %d",&v[num(i,j)],&x);
			for(int k=1;k<=x;k++)
			{
				scanf("%d %d",&p,&q);
				E[++edge_cnt].from=num(i,j);
				E[edge_cnt].to=num(p,q);
				ne[edge_cnt]=last[num(i,j)];
				last[num(i,j)]=edge_cnt;
				ru[num(p,q)]++;
			}
			for(int k=j+1;k<m;k++)
			{
				E[++edge_cnt].from=num(i,k);
				E[edge_cnt].to=num(i,j);
				ne[edge_cnt]=last[num(i,k)];
				last[num(i,k)]=edge_cnt;
				ru[num(i,j)]++;
			}
		}
	}
	edge_cnt1=1;
	make();
	//for(int i=1;i<=num(n-1,m-1);i++) printf("%d ",book[i]);
	while(bfs())
	{
		for(int i=1;i<=t;i++) cur[i]=last1[i];
		ans-=dinic(s,INF);
	}
	cout<<max(0,ans);
	return 0;
}