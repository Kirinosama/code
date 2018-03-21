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
int n,m,iscut[MAXM],dfn[MAXN],low[MAXN],ti;

void add_edge(int x,int y){
	E[++edge_cnt]=(edge){x,y};
	ne[edge_cnt]=last[x];
	last[x]=edge_cnt;
}

void tarjan(int x,int pre){
	dfn[x]=low[x]=++ti;
	for(int i=last[x];i;i=ne[i])if(i!=(pre^1)){
		int y=E[i].y;
		if(!dfn[y]){
			tarjan(y,i);
			low[x]=min(low[x],low[y]);
			if(low[y]>dfn[x]) iscut[i]=1;
		}else{
			low[x]=min(low[x],dfn[y]);
		}
	}
}

int main(){
    freopen("tarjan_gebian.in","r",stdin);
    cin>>n>>m;edge_cnt=1;
    for(int i=1;i<=m;i++){
    	int x,y;
    	scanf("%d%d",&x,&y);
    	add_edge(x,y);add_edge(y,x);
    }
    tarjan(1,-1);
    for(int i=1;i<=edge_cnt;i++)if(iscut[i])
    	printf("%d->%d\n",E[i].x,E[i].y);
    return 0;
}