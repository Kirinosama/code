#include <bits/stdc++.h>
using namespace std;

#define INF 0x3f3f3f3f
#define ii pair<int,int>
#define MAXN 100010
#define MAXM 2*MAXN
typedef long long ll;

int n,q;
int last[MAXN],ne[MAXM],edge_cnt;
int dep[MAXN],fa[MAXN][25];

struct edge{
	int x,y;
}E[MAXM];

void add_edge(int x,int y){
	E[++edge_cnt]=(edge){x,y};
	ne[edge_cnt]=last[x];
	last[x]=edge_cnt;
}

void dfs(int x,int f){
	fa[x][0]=f;dep[x]=dep[f]+1;
	for(int i=1;i<=20;i++)fa[x][i]=fa[fa[x][i-1]][i-1];
	for(int i=last[x];i;i=ne[i])if(E[i].y!=f)dfs(E[i].y,x);
}

int lca(int x,int y){
	if(dep[x]<dep[y])swap(x,y);
	for(int i=20;i>=0;i--)if(dep[x]-(1<<i)>=dep[y])
		x=fa[x][i];
	if(x==y) return x;
	for(int i=20;i>=0;i--)if(fa[x][i]!=fa[y][i])
		x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}

int dis(int x,int y){
	return dep[x]+dep[y]-2*dep[lca(x,y)];
}

bool judge(int p,int x,int y){
	if(dis(p,x)+dis(p,y)==dis(x,y)) return true;
	return false;
}

int main(){
	freopen("p3398.in","r",stdin);
	freopen("p3398.out","w",stdout);
	cin>>n>>q;
	for(int i=1;i<n;i++){
		static int x,y;
		scanf("%d%d",&x,&y);
		add_edge(x,y);add_edge(y,x);
	}
	dfs(1,1);
	while(q--){
		static int a,b,x,y;
		scanf("%d%d%d%d",&x,&y,&a,&b);
		if(judge(lca(x,y),a,b) || judge(lca(a,b),x,y))
			cout<<"Y"<<endl;
		else cout<<"N"<<endl;
	}
	return 0;
}
