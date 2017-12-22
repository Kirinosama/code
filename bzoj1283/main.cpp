#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#include <iostream>
using namespace std;

#define MAXN 2010
#define MAXM 10010
const int INF=0x7fffffff;

struct edge
{
	int from,to,flow,val;
}E[MAXM];

int last[MAXN],ne[MAXM],edge_cnt;
int n,m,k,s,t,ans,dis[MAXN],up[MAXN];
bool instack[MAXN];

int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}

void add(int x,int y,int flow,int val)
{
	E[++edge_cnt].from=x;
	E[edge_cnt].to=y;
	E[edge_cnt].flow=flow;
	E[edge_cnt].val=val;
	ne[edge_cnt]=last[x];
	last[x]=edge_cnt;
}

void insert(int x,int y,int flow,int val)
{
	add(x,y,flow,val);
	add(y,x,0,-val);
}

int spfa()
{
	int sum=0;
	int minflow=INF;
	queue <int> Q;
	memset(dis,-1,sizeof(dis));
	instack[s]=true;Q.push(s);dis[s]=0;
	while(!Q.empty())
	{
		int tp=Q.front();Q.pop();instack[tp]=false;
		for(int i=last[tp];i;i=ne[i])
		{
			int v=E[i].to;
			if(!E[i].flow) continue;
			if(dis[v]<dis[tp]+E[i].val)
			{
				dis[v]=dis[tp]+E[i].val;
				up[v]=i;
				if(!instack[v])
				{
					instack[v]=true;
					Q.push(v);
				}
			}
		}
	}
	if(dis[t]==-1) return 0;
	for(int i=t;i!=s;i=E[up[i]].from)
		minflow=min(minflow,E[up[i]].flow);
	for(int i=t;i!=s;i=E[up[i]].from)
	{
		E[up[i]].flow-=minflow;
		E[up[i]^1].flow+=minflow;
		sum+=minflow*E[up[i]].val;
	}
	return sum;
}

int main()
{
	freopen("input","r",stdin);
	scanf("%d %d %d",&n,&m,&k);
	edge_cnt=1;s=n+1;t=s+1;
	for(int i=1;i<=n;i++)
	{
		static int x;
		x=read();
		if(i+m<=n) insert(i,i+m,1,x);
		else insert(i,t,1,x);
	}
	for(int i=1;i<n;i++) insert(i,i+1,k,0);
	insert(s,1,k,0);insert(n,t,k,0);
	while(int tans=spfa()) 
		ans+=tans;
	cout<<ans;
	return 0;
}