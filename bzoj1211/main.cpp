#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <queue>
#include <iostream>
using namespace std;

#define MAXN 2010
#define MAXM MAXN*12
const int INF=0x7fffffff;

struct edge
{
	int from,to,flow,val;
}E[MAXM];

int edge_cnt,last[MAXN],ne[MAXM],n,m,f,fa,fb,a,b,ans;
int up[MAXN],dis[MAXN],s,t;
bool instack[MAXN];

int read()
{
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
    while(isdigit(ch)){x=x*10+ch-'0';ch=getchar();}
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
	int sumval=0;
	int minflow=INF;
	queue <int> Q;
	memset(dis,0x7f,sizeof(dis));
//	memset(instack,0,sizeof(instack));
	dis[s]=0;Q.push(s);instack[s]=true;
	while(!Q.empty())
	{
		int tp=Q.front();Q.pop();instack[tp]=false;
		for(int i=last[tp];i;i=ne[i])
		{
			int v=E[i].to;
			if(!E[i].flow) continue;
			if(dis[v]>dis[tp]+E[i].val)
			{
				dis[v]=dis[tp]+E[i].val;
				up[v]=i;
				if(!instack[v])
					Q.push(v),instack[v]=true;
			}
		}
	}
	if(dis[t]==0x7f7f7f7f) return 0;
	for(int i=t;i!=s;i=E[up[i]].from)
	{
		minflow=min(minflow,E[up[i]].flow);
		sumval+=E[up[i]].val;
	}
	for(int i=t;i!=s;i=E[up[i]].from)
	{
		E[up[i]].flow-=minflow;
		E[up[i]^1].flow+=minflow;
	}
	return minflow*sumval;
}

int main()
{
	freopen("input","r",stdin);
	scanf("%d %d %d %d %d %d",&n,&a,&b,&f,&fa,&fb);
	s=2*n+1;t=s+1;edge_cnt=1;
	for(int i=1;i<=n;i++)
	{
		static int x;
		x=read();
		insert(s,i,x,0);
		insert(i+n,t,x,0);
		insert(s,i+n,INF,f);
	}
	for(int i=1;i<n;i++) insert(i,i+1,INF,0);
	for(int i=1;i<=n;i++)
	{
		if(i+a+1<=n) insert(i,i+a+1+n,INF,fa);
		if(i+b+1<=n) insert(i,i+b+1+n,INF,fb);
	}
	while(int tans=spfa()) ans+=tans;
	cout<<ans;
	return 0;
}