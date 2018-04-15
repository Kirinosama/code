#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 100010
#define MAXM 200010

struct edge{
	int x,y;
}E[MAXM];

struct task{
	int type,x,ans;
	void in(){
		char c;
		scanf("\n%c %d",&c,&x);
		type=c=='C'?1:2;ans=1;
	}
}q[MAXN];

int last[MAXN],ne[MAXM],edge_cnt;
int anc[MAXN][21],dep[MAXN];
int n,m;

void add_edge(int x,int y){
	E[++edge_cnt]=(edge){x,y};
	ne[edge_cnt]=last[x];
	last[x]=edge_cnt;
}

void cdq(int l,int r){
	
}

void dfs(int x,int f){
	dep[x]=dep[f]+1;anc[x][0]=f;
	for(int i=1;i<=20;i++)anc[x][i]=anc[anc[x][i-1]][i-1];
	for(int i=last[x];i;i=ne[i])if(E[i].y!=f)
		dfs(E[i].y,x);
}

inline int lca(int x,int y){
	if(dep[x]<dep[y]) swap(x,y);
	for(int i=20;i>=0;i--)if(dep[x]-(1<<i)>=dep[y])
		x=anc[x][i];
	if(x==y) return x;
	for(int i=20;i>=0;i--)if(anc[x][i]!=anc[y][i])
		x=anc[x][i],y=anc[y][i];
	return anc[x][0];
}

int main(){
	freopen("bzoj4551.in","r",stdin);
	cin>>n>>m;
	for(int i=1;i<n;i++){
		int x,y;scanf("%d%d",&x,&y);
		add_edge(x,y);add_edge(y,x);
	}	
	dfs(1,1);
	for(int i=1;i<=m;i++)
		q[i].in();
	cdq(1,m);
	for(int i=1;i<=m;i++)if(q[i].type==2)
		cout<<q[i].ans<<endl;
	return 0;
}
