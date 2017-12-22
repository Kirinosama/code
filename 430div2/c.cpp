#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

#define MAXN 200010
#define MAXM 2*MAXN
const double eps=1e-8;

struct edge
{
	int from,to;
}E[MAXM];

int edge_cnt,last[MAXN],ne[MAXM],n,a[MAXN];
int f[MAXN][2];

int gcd(int x,int y)
{
	if(!x) return y;
	if(!y) return x;
	if(x>y) swap(x,y);
	return gcd(y%x,x);
}

void add(int x,int y)
{
	E[++edge_cnt].from=x;
	E[edge_cnt].to=y;
	ne[edge_cnt]=last[x];
	last[x]=edge_cnt;
}

void add_edge()
{
	int x,y;
	scanf("%d %d",&x,&y);
	add(x,y);
	add(y,x);
}

void dfs(int x,int fx)
{
	if(x!=1) 
	{
		f[x][1]=max(f[fx][0],gcd(f[fx][1],a[x]));
		f[x][0]=gcd(f[fx][0],a[x]);
	}
	for(int i=last[x];i;i=ne[i])
	{
		int v=E[i].to;
		if(v!=fx) dfs(v,x);
	}
}

int main()
{
	freopen("input","r",stdin);
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<n;i++) add_edge();
	f[1][1]=0;f[1][0]=a[1];
	dfs(1,-1);
	for(int i=1;i<=n;i++)
		printf("%d ",max(f[i][0],f[i][1]));
	return 0;
}