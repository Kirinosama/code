#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

#define MAXM 200010
#define MAXN 100010

struct edge
{
	int from,to;
}E[MAXM];

typedef long long ll;
int last[MAXN],ne[MAXM],edge_cnt,n;
int du[MAXN];
int col[MAXN];
ll ans,cnt[2];

void add(int x,int y)
{
	E[++edge_cnt].from=x;
	E[edge_cnt].to=y;
	ne[edge_cnt]=last[x];
	last[x]=edge_cnt;
	du[x]++;
}

void insert()
{
	int x,y;
	scanf("%d %d",&x,&y);
	add(x,y);add(y,x);
}

void dfs(int cur,int fa)
{
	for(int i=last[cur];i;i=ne[i])
	{
		int v=E[i].to;
		if(v==fa) continue;
		col[v]=!col[cur];
		cnt[col[v]]++;
		dfs(v,cur);
	}
}

int main()
{
	freopen("input","r",stdin);
	scanf("%d",&n);
	for(int i=1;i<n;i++) insert();
	col[1]=1;cnt[1]++;
	dfs(1,0);
	for(int i=1;i<=n;i++)
	{
		ans+=cnt[!col[i]];
		ans-=du[i];
	}
	ans>>=1;
	cout<<ans;
	return 0;
}