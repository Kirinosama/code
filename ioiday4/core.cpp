#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 100010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int w,t,c,n,father[MAXN],book[MAXN],in[MAXN],ans[MAXN],fa[MAXN];
int anc[MAXN][30],last[MAXN],ne[MAXN*2],dep[MAXN],edge_cnt;

struct Edge{
	int x,y;
}E[MAXN*2];

struct edge{
	int x,y;
}to[MAXN*2];

inline void add(int x,int y){
	to[++edge_cnt]=(edge){x,y};
	ne[edge_cnt]=last[x];
	last[x]=edge_cnt;
}

inline int find(int x){
	return father[x]==x?x:find(father[x]);
}

inline int lca(int x,int y){
	if(dep[x]<dep[y]) swap(x,y);
	for(int i=25;i>=0;i--)
		if(dep[x]-(1<<i)>=dep[y])
			x=anc[x][i];
	if(x==y) return x;
	for(int i=25;i>=0;i--)
		if(anc[x][i]!=anc[y][i])
			x=anc[x][i],y=anc[y][i];
	return fa[x];
}

inline int move(int x,int y){
	if(lca(x,y)!=x) return fa[x];
	for(int i=last[x];i;i=ne[i])
		if(to[i].y!=fa[x] && lca(to[i].y,y)==to[i].y)
			return to[i].y;
	return 0;
}

inline void dfs(int x,int k){
	int add;
	if(x==n){
		ans[k]=1;
		return;
	}
	for(int i=1;i<n;i++)
		if(!book[i] && in[E[i].x]+in[E[i].y]==1){
			if(!in[E[i].x]) add=E[i].x,in[E[i].x]=1;
			else add=E[i].y,in[E[i].y]=1;
			book[i]=1;
			int fx=find(E[i].x),fy=find(E[i].y);
			father[fx]=fy;
			dfs(x+1,move(k,add));
			in[add]=0;
			father[fx]=fx;
			book[i]=0;
		}
}

inline void make(int x,int f){
	fa[x]=anc[x][0]=f;dep[x]=dep[f]+1;
	for(int i=1;i<=25;i++)
		anc[x][i]=anc[anc[x][i-1]][i-1];
	for(int i=last[x];i;i=ne[i]){
		if(to[i].y!=f)
			make(to[i].y,x);
	}
}

inline void solve(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		father[i]=i,ans[i]=0;
	memset(last,0,sizeof(last));
	edge_cnt=0;in[1]=1;
	for(int i=1;i<n;i++){
		scanf("%d %d",&E[i].x,&E[i].y);
		add(E[i].x,E[i].y);
		add(E[i].y,E[i].x);
	}
	make(1,1);
	dfs(1,1);
	if(w!=3){
		for(int i=1;i<=n;i++)
			printf("%d",ans[i]);
		cout<<endl;
	}
	else cout<<ans[1]<<endl;
}

int main(){
    freopen("core.in","r",stdin);
    freopen("core.out","w",stdout);
    cin>>w>>t;
    while(t--)
    	solve();
    return 0;
}