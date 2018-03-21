#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 1000010
#define MAXM 2*MAXN
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

struct edge{
	int x,y;
}E[MAXM];

int edge_cnt,last[MAXN],ne[MAXM],n,a[MAXN],f[MAXN],cnt;
int dep[MAXN],anc[MAXN][26],dfn[MAXN],tail[MAXN],ti,m;
ll c[MAXN],s[MAXN];

void add_edge(int x,int y){
	E[++edge_cnt]=(edge){x,y};
	ne[edge_cnt]=last[x];
	last[x]=edge_cnt;
}

void dfs(int x,int fa){
	dfn[x]=++ti;dep[x]=dep[fa]+1;
	anc[x][0]=fa;f[x]=a[x];
	for(int i=1;i<=25;i++)anc[x][i]=anc[anc[x][i-1]][i-1];
	for(int i=last[x];i;i=ne[i])if(E[i].y!=fa){
		dfs(E[i].y,x);f[x]-=a[E[i].y];
	}
	tail[x]=ti;
}

int lowbit(int x){
	return x&-x;
}

void add(int x,int k){
	for(int i=x;i<=n;i+=lowbit(i))
		c[i]+=k;
}

ll getsum(int x){
	ll res=0;
	for(int i=x;i;i-=lowbit(i)) res+=c[i];
		return res;
}

int getlca(int x,int y){
	if(dep[x]<dep[y]) swap(x,y);
	for(int i=25;i>=0;i--)if(dep[x]-(1<<i)>=dep[y])
		x=anc[x][i];
	if(x==y) return x;
	for(int i=25;i>=0;i--)if(anc[x][i]!=anc[y][i])
		x=anc[x][i],y=anc[y][i];
	return anc[x][0];
}

ll cal(int x){
	return getsum(tail[x])-getsum(dfn[x]-1);
}

void dfs1(int x){
	for(int i=last[x];i;i=ne[i])if(E[i].y){
		s[++cnt]=cal(E[i].y);
	}
	s[++cnt]=cal(x);
}

int main(){
    freopen("T22222.in","r",stdin);
    cin>>n>>m;
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<n;i++){
    	int x,y;
    	scanf("%d%d",&x,&y);
    	add_edge(x,y),add_edge(y,x);
    }
	dfs(1,0);
	for(int i=1;i<=n;i++) add(dfn[i],f[i]);
	while(m--){
		int opt,x,y;
		scanf("%d%d%d",&opt,&x,&y);
		if(opt==1){
			int z;scanf("%d",&z);
			int lca=getlca(x,y);
			add(dfn[x],z);add(dfn[y],z);add(lca,-z);
			if(anc[lca][0]) add(anc[lca][0],-z);
		}else{
			cnt=0;dfs1(x);
			nth_element(s+1,s+y,s+cnt+1);
			printf("%lld\n",s[y]);
		}
	}
    return 0;
}