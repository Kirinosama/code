#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 1200010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int tot,n,T,cnt,dfn[MAXN],dep[MAXN],anc[MAXN][25],ID[MAXN],size[MAXN];
int a[MAXN],s[MAXN],book[MAXN],mindis[MAXN],ans[MAXN],belong[MAXN];

struct edge{
	int x,y;
};

struct graph{
	int edge_cnt,last[MAXN],ne[MAXN],vis[MAXN],lastvis;
	edge E[MAXN];
	void clear(){edge_cnt=0;memset(last,0,sizeof(last));}
	void add(int x,int y){
		E[++edge_cnt]=(edge){x,y};
		if(vis[x]==lastvis)ne[edge_cnt]=last[x];
		else vis[x]=lastvis,ne[edge_cnt]=0;
		last[x]=edge_cnt;
		E[++edge_cnt]=(edge){y,x};
		if(vis[y]==lastvis)ne[edge_cnt]=last[y];
		else vis[y]=lastvis,ne[edge_cnt]=0;
		last[y]=edge_cnt;
	}
	void dfs(int x,int f){
		dfn[x]=++cnt;dep[x]=dep[f]+1;
		anc[x][0]=f;size[x]=1;
		for(int i=1;i<=20;i++)anc[x][i]=anc[anc[x][i-1]][i-1];
		for(int i=last[x];i;i=ne[i]){
			int y=E[i].y;
			if(y==f) continue;
			dfs(y,x);size[x]+=size[y];
		}
	}
	ii dfs1(int x,int f){
		ii res(0,INF);
		for(int i=last[x];i;i=ne[i])if(E[i].y!=f){
			ii cur=dfs1(E[i].y,x);int len=dep[E[i].y]-dep[x];
			if(cur.second+len==res.second && cur.first<res.first) res.first=cur.first;
			if(cur.second+len<res.second) res.first=cur.first,res.second=cur.second+len;
		}
		if(book[x]) res.first=x,res.second=0;
		mindis[x]=res.second;belong[x]=res.first;
		return res;
	}
	void dfs2(int x,int f){
		int len=dep[x]-dep[f];
		if(mindis[x]==mindis[f]+len && belong[f]<belong[x]) belong[x]=belong[f];
		if(mindis[f]+len<mindis[x]) belong[x]=belong[f],mindis[x]=mindis[f]+len;
		for(int i=last[x];i;i=ne[i])if(E[i].y!=f)
			dfs2(E[i].y,x);
		ans[belong[x]]++;
	}
	void dfs3(int x,int f){
		ans[belong[x]]+=size[x]-1;
		for(int i=last[x];i;i=ne[i])if(E[i].y!=f)
			dfs3(E[i].y,x);
	}
}G1,G2;

bool cmp(const int &a,const int &b){
	return dfn[a]<dfn[b];
}

inline int getlca(int x,int y){
	if(dep[x]<dep[y])swap(x,y);
	for(int i=20;i>=0;i--)if(dep[x]-(1<<i)>=dep[y])
		x=anc[x][i];
	if(x==y) return x;
	for(int i=20;i>=0;i--)if(anc[x][i]!=anc[y][i])
		x=anc[x][i],y=anc[y][i];
	return anc[x][0];
}

inline int getdis(int x,int y){
	int lca=getlca(x,y);
	return dep[x]+dep[y]-2*dep[lca];
}

void make(int x,int y){
	if(dep[x]>dep[y]) swap(x,y);
	int son=y;
	for(int i=20;i>=0;i--)if(dep[son]-(1<<i)>dep[x]) 
		son=anc[son][i];
	ans[belong[x]]-=size[son];
	if(belong[x]==belong[y]){
		ans[belong[x]]+=size[son]-size[y];
		return;
	}
	int p=belong[x],q=belong[y],pos=y;
	for(int i=20;i>=0;i--)if((1<<i)<=dep[pos]-dep[x]-1){
		int to=anc[pos][i];
		if(q<p){
			if(getdis(q,to)<=getdis(p,to)) pos=to;
		}else{
			if(getdis(q,to)<getdis(p,to)) pos=to;
		}
	}
	ans[q]+=size[pos]-size[y];ans[p]+=size[son]-size[pos];
}

void solve(){
	int top=0;G2.lastvis++;G2.edge_cnt=0;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);ID[i]=a[i];
		book[a[i]]=1;ans[a[i]]=0;
	}
	if(n==1){
		printf("%d \n",tot);
		return;
	}
	sort(a+1,a+n+1,cmp);
	s[++top]=1;
	for(int i=1;i<=n;i++){
		int lca=getlca(s[top],a[i]);
		while(dep[lca]<dep[s[top]]){
			if(dep[s[top-1]]<=dep[lca]){
				if(lca==s[top-1]){
					G2.add(s[top],s[top-1]);
					top--;break;
				}else{
					G2.add(lca,s[top]);
					s[top]=lca;break;
				}
			}
			G2.add(s[top],s[top-1]);top--;
		}
		if(s[top]!=a[i]) s[++top]=a[i];
	}
	while(top>1) G2.add(s[top],s[top-1]),top--;
	G2.dfs1(1,1);G2.dfs2(1,1);G2.dfs3(1,1);
	for(int i=1;i<=G2.edge_cnt;i+=2)
		make(G2.E[i].x,G2.E[i].y);
	for(int i=1;i<=n;i++)printf("%d ",ans[ID[i]]);
	for(int i=1;i<=n;i++)book[a[i]]=0;
	printf("\n");
}

int main(){
    freopen("bzoj3572.in","r",stdin);
    freopen("out1","w",stdout);
    scanf("%d",&tot);G1.clear();
    for(int i=1;i<tot;i++){
    	int x,y;
    	scanf("%d%d",&x,&y);
    	G1.add(x,y);
    }
    G1.dfs(1,1);
    scanf("%d",&T);
	while(T--)
		solve();
    return 0;
}