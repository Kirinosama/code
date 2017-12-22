#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

#define MAXN 10010
#define MAXM 80010

struct edge
{
	int from,to;
}E[MAXM];

int to[MAXN],ne[MAXM],last[MAXN],vis[MAXN],col[MAXN],edge_cnt,ans,n,m,cnt;
int go[4][2]={{0,1},{0,-1},{-1,0},{1,0}};
char a[110][110];
int id[110][110];

int find(int x)
{
	for(int i=last[x];i;i=ne[i])
	{
		int v=E[i].to;
		if(!vis[v])
		{
			vis[v]=1;
			if(!to[v] || find(to[v]))
			{
				to[v]=x;
				return 1;
			}
		}
	}
	return 0;
}

void add(int x,int y)
{
	E[++edge_cnt].from=x;
	E[edge_cnt].to=y;
	ne[edge_cnt]=last[x];
	last[x]=edge_cnt;
}

int main()
{
	scanf("%d %d\n",&n,&m);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			scanf("%c",&a[i][j]);
			if(a[i][j]=='.') id[i][j]=++cnt;
		}
		scanf("\n");
	}
	memset(col,-1,sizeof(col));
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			for(int k=0;k<4;k++)
			{
				if(a[i][j]=='#') continue;
				if(col[id[i][j]]==-1) col[id[i][j]]=0;
				int tx=i+go[k][0];
				int ty=j+go[k][1];
				if(tx<1 || tx>n || ty<1 || ty>m || a[tx][ty]=='#') continue;
				if(col[id[i][j]]==0) add(id[i][j],id[tx][ty]);
				col[id[tx][ty]]=col[id[i][j]]^1;
			}	
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			if(a[i][j]=='.' && col[id[i][j]]==0)
			{
				memset(vis,0,sizeof(vis));
				ans+=find(id[i][j]);
			}
		}
	if(ans*2==cnt)
	{
		printf("LOSE");
		return 0;
	}
	for(int i=1;i<=cnt;i++) book[to[i]]=1;
	for(int i=1;i<=cnt;i++)
	{
		if(id[i]==0 && !book[i])
		{
			v.push_back()
		}
	}
	return 0;
}