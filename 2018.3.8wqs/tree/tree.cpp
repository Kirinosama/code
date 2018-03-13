#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 40010
#define MAXM 2*MAXN
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int n,m,dep[MAXN],anc[MAXN][25],root,last[MAXN],ne[MAXM],edge_cnt;

struct edge{
	int x,y;
}E[MAXM];

void add_edge(int x,int y){
	E[++edge_cnt]=(edge){x,y};
	ne[edge_cnt]=last[x];
	last[x]=edge_cnt;
}

void dfs(int x,int f){
	dep[x]=dep[f]+1;anc[x][0]=f;
	for(int i=1;i<=20;i++)anc[x][i]=anc[anc[x][i-1]][i-1];
	for(int i=last[x];i;i=ne[i])if(E[i].y!=f)
		dfs(E[i].y,x);
}

int solve(int x,int y){
	if(dep[x]<dep[y]){
		for(int i=20;i>=0;i--)if(dep[y]-(1<<i)>=dep[x])
			y=anc[y][i];
		return x==y?1:0;
	}else{
		for(int i=20;i>=0;i--)if(dep[x]-(1<<i)>=dep[y])
			x=anc[x][i];
		return x==y?2:0;
	}
}

int main(){
    freopen("tree.in","r",stdin);
    freopen("tree.out","w",stdout);
    cin>>n;
    for(int i=1;i<=n;i++){
    	int x,y;
    	scanf("%d%d",&x,&y);
    	if(y==-1) root=x;
    	else add_edge(x,y),add_edge(y,x);
    }
    dfs(root,root);
    cin>>m;
    for(int i=1;i<=m;i++){
    	int x,y;
    	scanf("%d%d",&x,&y);
    	printf("%d\n",solve(x,y));
    }
    return 0;
}