#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

#define MAXN 110
#define MAXM 110
const int INF=0x7fffffff;

struct edge
{
	int from,to,k;
}E[MAXM];

int n,m,edge_cnt,last[MAXN],ne[MAXM];
int dis[MAXN],l[MAXN],r[MAXN],tree[MAXN];
int f[MAXN][60][MAXN],v[MAXN];

void add(int x,int y,int z)
{
	E[++edge_cnt].from=x;
	E[edge_cnt].to=y;
	E[edge_cnt].k=z;
	ne[edge_cnt]=last[x];
	last[x]=edge_cnt;
}

void dfs(int x,int fa)
{
	for(int i=last[x];i;i=ne[i])
	{
		int v=E[i].to;
		if(v!=fa)
		{
			dis[v]=dis[x]+E[i].k;
			dfs(v,x);
		}
	}
}

int dp(int i,int j,int k)
{
	int ans=0;
	if(f[i][j][k]!=-1) return f[i][j][k];
	f[i][j][k]=INF;
	for(int h=0;h<=j;h++)
	{
		ans=v[i]*(dis[i]-dis[k]);
		if(l[i]) ans+=dp(l[i],h,k);
		if(r[i]) ans+=dp(r[i],j-h,k);
		f[i][j][k]=min(f[i][j][k],ans);
		if(h<j)
		{
			ans=0;
			if(l[i]) ans+=dp(l[i],h,i);
			if(r[i]) ans+=dp(r[i],j-h-1,k);
			f[i][j][k]=min(f[i][j][k],ans);
		}
	}
	return f[i][j][k];
}

int main()
{
	freopen("input","r",stdin);
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		int y,z;
		scanf("%d %d %d",&v[i],&y,&z);
		if(!tree[y]) {l[y]=i;tree[y]=i;}
		else {r[tree[y]]=i;tree[y]=i;}
		add(y,i,z);
	}
	dfs(0,0);memset(f,-1,sizeof(f));
//	for(int i=0;i<=n;i++)
//		printf("%d %d %d %d\n",i,l[i],r[i],dis[i]);
	printf("%d",dp(0,m,0));
	return 0;
}