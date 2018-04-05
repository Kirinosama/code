#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 100010
#define MAXM 200010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

struct edge{
	int x,y;
}E[MAXM];

int edge_cnt,last[MAXN],ne[MAXM];
int n,m,iscut[MAXN],dfn[MAXN],low[MAXN],ti;

void add_edge(int x,int y){
	E[++edge_cnt]=(edge){x,y};
	ne[edge_cnt]=last[x];
	last[x]=edge_cnt;
}

void tarjan(int x,int pre){
	int child=0;
	dfn[x]=low[x]=++ti;
	for(int i=last[x];i;i=ne[i])if(i!=(pre^1)){
		int y=E[i].y;
		if(!dfn[y]){
			child++;tarjan(y,i);
			low[x]=min(low[x],low[y]);
			if(low[y]>=dfn[x]) iscut[x]=1;
		}else{
			low[x]=min(low[x],dfn[y]);
		}
	}
	if(pre==-1 && child==1) iscut[x]=0;
}

int main(){
    freopen("tarjan_gedian.in","r",stdin);
    cin>>n>>m;edge_cnt=1;
    for(int i=1;i<=m;i++){
    	int x,y;
    	scanf("%d%d",&x,&y);
    	add_edge(x,y);add_edge(y,x);
    }
    tarjan(1,-1);
    for(int i=1;i<=n;i++)if(iscut[i])
    	printf("%d ",i);
    return 0;
}
