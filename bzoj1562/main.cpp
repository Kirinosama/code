#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;

#define MAXN 20010
#define MAXM MAXN*2

struct edge
{
	int from,to;
}E[MAXM];

int last[MAXN],ne[MAXM],edge_cnt;
int vis[MAXN],lk[MAXN],ans,anss[MAXN],n,x;

void add(int x,int y)
{
	E[++edge_cnt].from=x;
	E[edge_cnt].to=y;
	ne[edge_cnt]=last[x];
	last[x]=edge_cnt;
}

int find(int x)
{
	vis[x]=1;
	for(int i=last[x];i;i=ne[i])
	{
		int v=E[i].to;
		if(!vis[v])
		{
			vis[v]=1;
			if(!lk[v] || find(lk[v]))
			{
				lk[v]=x; return 1;
			}
		}
	}
	return 0;
}

int main()
{
	freopen("input","r",stdin);
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		scanf("%d",&x);
		int a=i-x; if(a<0) a+=n;
		int b=i+x; if(b>=n) b-=n;
		a%=n;b%=n;
		if(a<b) swap(a,b);
		add(i,a+n);add(i,b+n);
	}
	for(int i=n-1;i>=0;i--)
	{
		memset(vis,0,sizeof(vis));
		if(find(i))
			ans++;
	}
	if(ans!=n) printf("No Answer");
	else
	{
		for(int i=0;i<n;i++) anss[lk[i+n]]=i;
		for(int i=0;i<n;i++)
		{
			printf("%d",anss[i]);
			if(i!=n-1) printf(" ");
		}
	}
	return 0;
}