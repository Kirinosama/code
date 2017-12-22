#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

#define MAXN 3010
#define MAXM 20010

const double eps=0.000000001;
int n,m,last[MAXN],ne[MAXM],edge_cnt,flag;
int vis[MAXN];
double ans,dis[MAXN];

struct edge
{
	int from,to;
	double k;
}E[MAXM];

void add()
{
	int x,y;
	double k;
	scanf("%d %d %lf",&x,&y,&k);
	E[++edge_cnt].from=x;
	E[edge_cnt].to=y;
	E[edge_cnt].k=k;
	ne[edge_cnt]=last[x];
	last[x]=edge_cnt;
}

void spfa(int x)
{
	vis[x]=1;
	for(int i=last[x];i;i=ne[i])
	{
		int v=E[i].to;
		if(dis[v]>dis[x]+E[i].k)
		{
			if(vis[v])
			{
				flag=1;return;
			}
			dis[v]=dis[x]+E[i].k;
			spfa(v);
		}
	}
	vis[x]=0;
}

bool judge(double x)
{
	memset(vis,0,sizeof(vis));	
	memset(dis,0,sizeof(dis));
	for(int i=1;i<=edge_cnt;i++)E[i].k-=x;
	flag=0;
	for(int i=1;i<=n;i++) 	
	{
		spfa(i);
		if(flag) break;
	}
	for(int i=1;i<=edge_cnt;i++)E[i].k+=x;
	if(flag) return true;
	return false;
}

int main()
{
	freopen("input","r",stdin);
	scanf("%d %d",&n,&m);
	for(int i=1;i<=m;i++) add();	
	double l=-10000000.0;double r=10000000.0;
	while(r-l>eps)
	{
	//		printf("%lf %lf %lf\n",l,r,ans);
		double mid=(l+r)/2.0;
		if(judge(mid)) 	ans=mid,r=mid;
		else l=mid;
	}
	printf("%.8f",ans);
	return 0;
}