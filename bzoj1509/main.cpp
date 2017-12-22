#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

typedef long long ll;
#define MAXN 200010
#define MAXM MAXN*2
const int INF=1e9;

int n,m,a,b,p;
ll disa[MAXN],disb[MAXN],ans;
int ne[MAXM],last[MAXN],edge_cnt,vis[MAXN];

struct edge
{
	int from,to,k;
}E[MAXM];

void add(int x,int y,int k)
{
	E[++edge_cnt].from=x;
	E[edge_cnt].to=y;
	E[edge_cnt].k=k;
	ne[edge_cnt]=last[x];
	last[x]=edge_cnt;
}

void dfs(int x,ll *s)
{
	for(int i=last[x];i;i=ne[i])
	{
		int v=E[i].to;
		if(!vis[v])
		{
			vis[v]=1;s[v]=s[x]+E[i].k;
			if(s[v]>ans)
			{
				ans=s[v];
				p=v;
			}
			dfs(v,s);
		}
	}
}

int main()
{
	freopen("input","r",stdin);
	scanf("%d %d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		static int x,y,k;
		scanf("%d %d %d",&x,&y,&k);
		add(x,y,k);add(y,x,k);
	}
	ans=-INF;vis[1]=1;dfs(1,disa);a=p;
	memset(vis,0,sizeof(vis));disa[a]=0;
	ans=-INF;vis[a]=1;dfs(a,disa);b=p;
	memset(vis,0,sizeof(vis));
	ans=-INF;vis[b]=1;dfs(b,disb);
	ans=-INF;
	for(int i=1;i<=n;i++)
	{
		if(i!=a || i!=b)
			ans=max(ans,min(disa[i],disb[i]));
	}
	printf("%lld",disa[b]+ans);
	return 0;
}