#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 10010
#define MAXM 20010

struct edge
{
	int from,to,z;
}E[MAXM];


int deep[MAXN];
int sum,f[MAXN],root,ans,last[MAXN],ne[MAXM],edge_cnt;
int son[MAXN],vis[MAXN],dis[MAXN],n,k;

void add(int x,int y,int z)
{
	E[++edge_cnt]=(edge){x,y,z};
	ne[edge_cnt]=last[x];
	last[x]=edge_cnt;	
}

void insert()
{
	int x,y,z;
	scanf("%d %d %d",&x,&y,&z);
	add(x,y,z);
	add(y,x,z);
}

void getroot(int cur,int fa)
{
	son[cur]=1;f[cur]=0;
	for(int i=last[cur];i;i=ne[i])
	{
		int 	v=E[i].to;
		if(vis[v] || v==fa) continue;
		getroot(v,cur);
		son[cur]+=son[v];
		f[cur]=max(f[cur],son[v]);
	}
	f[cur]=max(f[cur],sum-son[cur]);
	if(f[cur]<f[root]) root=cur; 
}

void getdeep(int x,int fa)
{
	deep[++deep[0]]=dis[x];
	for(int i=last[x];i;i=ne[i])
	{
		int v=E[i].to;
		if(vis[v] || fa==v) continue;
		dis[v]=dis[x]+E[i].z;
		getdeep(v,x);
	}
}

int cal(int x,int d)
{
	int res=0;
	dis[x]=d;
	deep[0]=0;
	getdeep(x,0);
	sort(deep+1,deep+1+deep[0]);
	int l=1;int r=deep[0];
	while(l<r)
	{
		if(deep[r]+deep[l]<=k)
			res+=r-l,l++;
		else r--;
	}
	return res;
}

void make(int cur)
{	
	ans+=cal(cur,0);
	vis[cur]=1;
	for(int i=last[cur];i;i=ne[cur])
	{
		int v=E[i].to;
		if(vis[v]) continue;
		ans-=cal(v,E[i].z);
		sum=son[v];
		root=0;
		getroot(v,root);
		make(root);
	}
}

int main()
{
	freopen("input","r",stdin);
	while(1)
	{
		scanf("%d %d",&n,&k);
		if(!n) break;
		edge_cnt=0;	f[0]=0x7fffffff;root=0;sum=n;ans=0;
		memset(last,0,sizeof(last));
		memset(vis,0,sizeof(vis));
		for(int i=1;i<n;i++) insert();
		getroot(1,0);
		make(root);
		printf("%d\n",ans);
	}
	return 0;	
}