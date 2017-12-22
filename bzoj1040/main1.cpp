#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

#define MAXN 1000010
#define MAXM 2000020
#define judge(x,y) ((x+1==y || y+1==x)?1:0)
typedef long long ll;

struct edge
{
	int from,to;
}E[MAXM];

int n,w[MAXN],t,edge_cnt,last[MAXN],ne[MAXM];
int tree_cnt,root[MAXN],dfn[MAXN];
int book[MAXN],cant1,cant2;
ll ans,dp[MAXN][2];

void insert(int u,int v)
{
	E[++edge_cnt].from=u;
	E[edge_cnt].to=v;
	ne[edge_cnt]=last[u];
	last[u]=edge_cnt;
}

void dfs(int x)
{
	book[x]=1;
	for(int i=last[x];i;i=ne[i])
		if(!book[E[i].to])
			dfs(E[i].to);
}	

void find(int pos,int fa,int &x,int &y)
{
	dfn[pos]=1;
	for(int i=last[pos];i;i=ne[i])
	{
		if(judge(i,fa)) continue;
		if(!dfn[E[i].to])
			find(E[i].to,i,x,y);
		else
		{
			x=pos,y=E[i].to;
			cant1=i;cant2=i%2?i+1:i-1;
			return;
		}
	}
}

ll val(int pos,int fa,int ch,int l,int r)
{
	if(dp[pos][ch])
		return dp[pos][ch];
	for(int i=last[pos];i;i=ne[i])
	{
		if(i==cant1 || i==cant2) continue;
		if(E[i].to==fa)	continue;
		if(ch==1) dp[pos][ch]+=val(E[i].to,pos,0,l,r);
		if(ch==0) dp[pos][ch]+=max(val(E[i].to,pos,1,l,r),val(E[i].to,pos,0,l,r));
	}
	if(ch==1) return dp[pos][ch]=dp[pos][ch]+w[pos];
	else return dp[pos][ch];
}

void solve(int pos)
{
	int x,y;
	ll res=-1;
	find(root[pos],-1,x,y);
	memset(dp,0,sizeof(dp));
	res=max(res,val(x,x,0,x,y));
	memset(dp,0,sizeof(dp));
	res=max(res,val(y,y,0,x,y));
	ans+=res;
}

int main()
{
	freopen("input","r",stdin);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d %d",&w[i],&t);
		insert(i,t);
		insert(t,i);
	}
	for(int i=1;i<=n;i++)
	{
		if(!book[i])
		{
			tree_cnt++;
			root[tree_cnt]=i;
			dfs(i);
		}
	}
	for(int i=1;i<=tree_cnt;i++)
		solve(i);
	printf("%lld",ans);
	return 0;
}
