#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <queue>
#include <iostream>
using namespace std;

#define INF 0x3f3f3f3f
#define MAXN 2010
#define MAXM 200010

struct edge
{
	int from,to,f;
}E[MAXM];

int edge_cnt,last[MAXN],ne[MAXM],n,m,k,x,s,t,book[MAXN];
int dis[MAXN],ans,cur[MAXN],la[MAXN];

inline int read()
{
    int data=0,w=1; char ch=0;
    while(ch!='-' && (ch<'0' || ch>'9')) ch=getchar();
    if(ch=='-') w=-1,ch=getchar();
    while(ch>='0' && ch<='9') data=data*10+ch-'0',ch=getchar();
    return data*w;
}

void add(int x,int y,int f)
{
	E[++edge_cnt].from=x;
	E[edge_cnt].to=y;
	E[edge_cnt].f=f;
	ne[edge_cnt]=last[x];
	last[x]=edge_cnt;
}

void insert(int x,int y,int f)
{
	add(x,y,f);add(y,x,0);
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
	int sum=0;
	int tmp=0;
	if(x==t) return f;
	for(int &i=cur[x];i;i=ne[i])
	{
		int v=E[i].to;
		if(dis[v]==dis[x]+1 && E[i].f)
		{
			tmp=dinic(v,min(f-sum,E[i].f));
			E[i].f-=tmp;E[i^1].f+=tmp;sum+=tmp;
			if(sum==f) return sum;
		}
	}
	if(!sum) dis[x]=-1;
	return sum;
}

int main()
{
	freopen("input","r",stdin);
	scanf("%d%d" , &m , &n) , s = 0 , t = m + n + 1;edge_cnt=1;
	for(int i = 1 ; i <= m ; i ++ ) scanf("%d" , &x) , insert(s , i , x);
	for(int i = 1 ; i <= n ; i ++ )
	{
		scanf("%d" , &k);
		while(k -- )
		{
			scanf("%d" , &x);
			if(la[x]) insert(la[x] + m , i + m , INF);
			else insert(x , i + m , INF);
			la[x] = i;
		}
		scanf("%d" , &x) , insert(i + m , t , x);
	}
	while(bfs())
	{
		for(int i=0;i<=t;i++) cur[i]=last[i];
			ans+=dinic(s,INF);
	}
	cout<<ans;
	return 0;
}