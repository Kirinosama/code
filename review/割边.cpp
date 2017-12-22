#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

#define MAXN 100010
#define MAXM 200010

int last[MAXN],ne[MAXM],edge_cnt,n,m;
int dfn[MAXN],low[MAXN],ti;

struct edge{
	int x,y;
}E[MAXM];

void add(int x,int y){
	E[++edge_cnt]=(edge){x,y};
	ne[edge_cnt]=last[x];
	last[x]=edge_cnt;
}

void tarjan(int x,int fa){
	dfn[x]=low[x]=++ti;
	for(int i=last[x];i;i=ne[i]){
		int v=E[i].y;
		if(v==fa) continue;
		if(!dfn[v]){
			tarjan(v,x);
			low[x]=min(low[x],low[v]);
			if(low[v]>dfn[x]) printf("%d %d\n",x,v);
		}
		else low[x]=min(low[x],dfn[v]);
	}
}

int main(){
	freopen("input","r",stdin);
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		static int x,y;
		scanf("%d %d",&x,&y);
		add(x,y),add(y,x);
	}
	for(int i=1;i<=n;i++)
		if(!dfn[i])
			tarjan(i,i);
	return 0;
}