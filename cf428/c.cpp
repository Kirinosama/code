#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

#define MAXN 100010
#define MAXM 2*MAXN

struct edge
{
	int from,to;
}E[MAXM];

int ne[MAXM],last[MAXN],edge_cnt,n;

void add(int x,int y)
{
	E[++edge_cnt].from=x;
	E[edge_cnt].to=y;
	ne[edge_cnt]=last[x];
	last[x]=edge_cnt;
}

double dfs(int x,int fa,double p,int len)
{
	int cnt=0;
	double sum=0;
	for(int i=last[x];i;i=ne[i])
		if(E[i].to!=fa) cnt++;
	for(int i=last[x];i;i=ne[i])
	{
		int v=E[i].to;
		if(v==fa) continue;
		sum+=dfs(v,x,p/cnt,len+1);
	}
	if(!sum) return p*len;
	else return sum;
}

int main()
{
	freopen("input","r",stdin);
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		static int x,y;
		scanf("%d %d",&x,&y);
		add(x,y),add(y,x);
	}	
	printf("%.15f",dfs(1,-1,1.0,0));
	return 0;
}