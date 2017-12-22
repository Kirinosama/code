#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 410
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int root,node_cnt,to[MAXN][30],anc[MAXN][25],dep[MAXN],t[4];
int num[4],edge_cnt,last[MAXN],ne[MAXN];
string s[4];

struct edge{
	int x,y;
}E[MAXN];

inline void add_edge(int x,int y){
	E[++edge_cnt]=(edge){x,y};
	ne[edge_cnt]=last[x];
	last[x]=edge_cnt;
}

inline void insert(int id,string s){
	int cur=root;
	for(int i=0;i<s.length();i++){
		int c=s[i]-'A';
		if(!to[cur][c]){
			to[cur][c]=++node_cnt;
			add_edge(cur,node_cnt);
			add_edge(node_cnt,cur);
		}
		cur=to[cur][c];
	}
	t[id]=cur;
}

inline int lca(int x,int y){
	if(dep[x]<dep[y]) swap(x,y);
	for(int i=20;i>=0;i--)
		if(dep[x]-(1<<i)>=dep[y])
			x=anc[x][i];
	if(x==y) return x;
	for(int i=20;i>=0;i--)
		if(anc[x][i]!=anc[y][i])
			x=anc[x][i],y=anc[y][i];
	return anc[x][0];
}

inline int dis(int x,int y){
	return dep[x]+dep[y]-2*dep[lca(x,y)];
}

inline void dfs(int x,int fa){
	anc[x][0]=fa,dep[x]=dep[fa]+1;
	for(int i=1;i<=20;i++)
		anc[x][i]=anc[anc[x][i-1]][i-1];
	for(int i=last[x];i;i=ne[i])
		if(E[i].y!=fa) dfs(E[i].y,x);
}

inline int cal(int x){
	return dis(t[1],x)+dis(t[2],x)+dis(t[3],x);
}

inline void solve(){
	int a=lca(t[1],t[2]),b=lca(t[1],t[3]),c=lca(t[2],t[3]);
	if(a==b) printf("%d",cal(c));
	else if(a==c) printf("%d",cal(b));
	else printf("%d",cal(a));
}

int main(){
    freopen("bzoj1789.in","r",stdin);
    freopen("out1","w",stdout);
    root=++node_cnt;
    for(int i=1;i<=3;i++){
    	scanf("%d",&num[i]);
    	if(num[i])cin>>s[i],insert(i,s[i]);
    	else t[i]=1;
    }
    dfs(1,1);
    solve();
    return 0;
}