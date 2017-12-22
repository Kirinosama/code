#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

#define MAXN 12000
#define MAXM 2*MAXN
const int INF=10010;


struct edge
{
	int from,to;
}E[MAXM];

int n,m,c[MAXN],edge_cnt,last[MAXN],ne[MAXM],f[MAXN][2];

inline void add(int x,int y)
{
	E[++edge_cnt].from=x;
	E[edge_cnt].to=y;
	ne[edge_cnt]=last[x];
	last[x]=edge_cnt;
}

inline void insert()
{
	int x,y;
	scanf("%d %d",&x,&y);
	add(x,y),add(y,x);
}

inline void dfs(int x,int fa)
{
	f[x][0]=f[x][1]=1;
	if(x<=m && c[x]==0) f[x][1]=INF;
	if(x<=m && c[x]==1) f[x][0]=INF;
	for(int i=last[x];i;i=ne[i])
	{
		int v=E[i].to;
		if(v==fa) continue;
		dfs(v,x);
		f[x][0]+=min(f[v][0]-1,f[v][1]);
		f[x][1]+=min(f[v][1]-1,f[v][0]);
	}
}

int main()
{
	freopen("input","r",stdin);	
	scanf("%d %d",&n,&m);
	for(int i=1;i<=m;i++) scanf("%d",&c[i]);
	for(int i=1;i<n;i++) insert();
	dfs(m+1,-1);
	cout<<min(f[m+1][0],f[m+1][1]);
	return 0;
}