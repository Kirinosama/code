#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 300010
#define MAXM 2*MAXN
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

struct edge{
	int x,y;
}E[MAXM];

int last[MAXN],ne[MAXM],edge_cnt;
int n,fa[MAXN],f[MAXN],a[MAXN],anc[MAXN][30],dep[MAXN];

void add(int x,int y){
	E[++edge_cnt]=(edge){x,y};
	ne[edge_cnt]=last[x];
	last[x]=edge_cnt;
}

void dfs(int x,int pre){
	fa[x]=anc[x][0]=pre;dep[x]=dep[pre]+1;
	for(int i=1;i<=25;i++) anc[x][i]=anc[anc[x][i-1]][i-1];
	for(int i=last[x];i;i=ne[i])if(E[i].y!=pre){
		dfs(E[i].y,x);
	}
}

void dfs1(int x){
	for(int i=last[x];i;i=ne[i])if(E[i].y!=fa[x]){
		dfs1(E[i].y);f[x]+=f[E[i].y];
	}
}

inline int getlca(int x,int y){
	if(dep[x]<dep[y]) swap(x,y);
	for(int i=25;i>=0;i--)if(dep[x]-(1<<i)>=dep[y]){
		x=anc[x][i];
	}
	if(x==y) return x;
	for(int i=25;i>=0;i--)if(anc[x][i]!=anc[y][i]){
		x=anc[x][i],y=anc[y][i];
	}
	return anc[x][0];
}

int main(){
    freopen("bzoj3631.in","r",stdin);
    freopen("out1","w",stdout);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    for(int i=1;i<n;i++){
    	int x,y;
    	scanf("%d%d",&x,&y);
    	add(x,y);add(y,x);
    }
    dfs(1,0);
   	for(int i=1;i<n;i++){
   		f[a[i]]++;f[a[i+1]]++;
   		int lca=getlca(a[i],a[i+1]);
   		f[lca]--;f[fa[lca]]--;
   	}
   	dfs1(1);f[a[1]]++;
   	for(int i=1;i<=n;i++){
   		printf("%d\n",f[i]-1);
   	}
    return 0;
}