#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

#define MAXN 10010
#define MAXM 20020
const int INF=0x3f3f3f3f;

int f[MAXN][25],ans,last[MAXN],edge_cnt,ne[MAXM],n;

struct edge
{
	int from,to;
}E[MAXM];

void add(int x,int y)
{
	E[++edge_cnt].from=x;
	E[edge_cnt].to=y;
	ne[edge_cnt]=last[x];
	last[x]=edge_cnt;
}

void dfs(int x,int fa)
{
	for(int i=1;i<=20;i++) f[x][i]=i;
	for(int i=last[x];i;i=ne[i])
	{
		int v=E[i].to;
		if(v==fa) continue;
		dfs(v,x);
		for(int j=1;j<=20;j++)
		{
			int mn=INF;
			for(int k=1;k<=20;k++)
				if(j!=k) mn=min(mn,f[v][k]);
			f[x][j]+=mn;
		}
	}
}

int main()
{
	freopen("input","r",stdin);
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		static int x,y;
		scanf("%d %d",&x,&y);
		add(x,y);add(y,x);
	}
	dfs(1,-1);	ans=INF;
	for(int i=1;i<=20;i++)
		ans=min(ans,f[1][i]);
	cout<<ans;
	return 0;
}