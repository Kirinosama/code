#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;

#define MAXN 310

int edge_cnt,n,w[MAXN],ans,father[MAXN];

struct node
{
	int from,to,v;
	bool operator < (node a)const{
		return v<a.v;
	}
}e[MAXN*MAXN];

int find(int x){
	return father[x]= father[x]==x ? x : find(father[x]);
}

void merge(int x,int y){
	int fx=find(x),fy=find(y);
	if(fx!=fy) father[fx]=fy;
}

void kruskal()
{
	int cnt=0;
	for(int i=1;i<=n+1;i++) father[i]=i;
	for(int i=1;i<=edge_cnt;i++)
	{
		int u=e[i].from;int v=e[i].to;
		if(find(u)!=find(v))
		{
			cnt++;merge(u,v);ans+=e[i].v;
		}
		if(cnt==n) return;
	}
}

int main()
{
	freopen("input","r",stdin);
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&w[i]);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			static int x;
			scanf("%d",&x);
			if(i<j)
			{
				e[++edge_cnt].from=i;
				e[edge_cnt].to=j;
				e[edge_cnt].v=x;
			}
		}
	for(int i=1;i<=n;i++)
		e[++edge_cnt].from=n+1,e[edge_cnt].to=i,e[edge_cnt].v=w[i];
	sort(e+1,e+1+edge_cnt);
	kruskal();
	cout<<ans;
	return 0;
}