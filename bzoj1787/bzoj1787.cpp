#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define MAXN 500010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

vector <int> to[MAXN];
int n,m,p[4],a,b,c,anc[MAXN][25],dep[MAXN];

inline bool cmp(const int &a,const int &b){
	return dep[a]<dep[b];
}

inline void add_edge(){
	static int x,y;
	scanf("%d %d",&x,&y);
	to[x].push_back(y);
	to[y].push_back(x);
}

inline void dfs(int x,int fa){
	anc[x][0]=fa;dep[x]=dep[fa]+1;
	for(int i=1;i<=20;i++)
		anc[x][i]=anc[anc[x][i-1]][i-1];
	for(int i=0;i<to[x].size();i++){
		int y=to[x][i];
		if(y!=fa)dfs(y,x);
	}
}

inline int lca(int x,int y){
	if(dep[x]<dep[y]) swap(x,y);
	for(int i=22;i>=0;i--)
		if(dep[x]-(1<<i)>=dep[y])
			x=anc[x][i];
	if(x==y) return x;
	for(int i=22;i>=0;i--)
		if(anc[x][i]!=anc[y][i])
			x=anc[x][i],y=anc[y][i];
	return anc[x][0];
}

inline int dis(int x,int y){
	return dep[x]+dep[y]-2*dep[lca(x,y)];
}

inline int cal(int x){
	return dis(x,p[1])+dis(x,p[2])+dis(x,p[3]);
}

inline void solve(){
	scanf("%d %d %d",&p[1],&p[2],&p[3]);
	a=lca(p[1],p[2]),b=lca(p[1],p[3]),c=lca(p[2],p[3]);
	if(a==b) printf("%d %d\n",c,cal(c));
	else if(a==c) printf("%d %d\n",b,cal(b));
	else printf("%d %d\n",a,cal(a));
}

int main(){
    freopen("bzoj1787.in","r",stdin);
    scanf("%d %d",&n,&m);
    for(int i=1;i<n;i++)
    	add_edge();
    dfs(1,1);
    while(m--)
    	solve();
    return 0;
}