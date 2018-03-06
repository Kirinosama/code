#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

#define MAXN 100010
#define MAXM 200010
#define MOD 10000000007
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

struct edge{
	int x,y;
};

struct graph{
	int last[MAXN],ne[MAXM],edge_cnt;
	edge E[MAXM];
	graph(){edge_cnt=0,memset(last,0,sizeof(last));}
	void add(int x,int y){
		E[++edge_cnt]=(edge){x,y};
		ne[edge_cnt]=last[x];
		last[x]=edge_cnt;
	}
}g1,g2;

map <int,int> mp1[MAXN],mp2[MAXN];
int a[MAXN],b[MAXN],vis[MAXN],val[MAXN],fa[MAXN],n,g[MAXN],size[MAXN];
int tot,root,dep[MAXN],anc[MAXN][21],dp[MAXN],all[MAXN];

inline int getlca(int x,int y){
	if(dep[x]<dep[y]) swap(x,y);
	for(int i=20;i>=0;i--)if(dep[x]-(1<<i)>=dep[y])
		x=anc[x][i];
	if(x==y) return x;
	for(int i=20;i>=0;i--)if(anc[x][i]!=anc[y][i])
		x=anc[x][i],y=anc[y][i];
	return anc[x][0];
}

void getroot(int x,int f){
	g[x]=0;size[x]=1;
	for(int i=g1.last[x];i;i=g1.ne[i]){
		int y=g1.E[i].y;
		if(vis[y] || y==f) continue;
		getroot(y,x);size[x]+=size[y];
		g[x]=max(g[x],size[y]);
	}
	g[x]=max(g[x],tot-size[x]);
	if(g[x]<g[root]) root=x;
}

void dfs1(int x,int f,int dis,int G1,int G2){
	if(mp1[G1].find(dis)==mp1[G1].end()) mp1[G1][dis]=1;
	else mp1[G1][dis]=mp1[G1][dis]+1;
	if(mp2[G2].find(dis)==mp2[G2].end()) mp2[G2][dis]=1;
	else mp2[G2][dis]=mp2[G2][dis]+1;
	for(int i=g1.last[x];i;i=g1.ne[i]){
		int y=g1.E[i].y;
		if(y==f || vis[y]) continue;
		dfs1(y,x,dis+a[y],G1,G2);
	}
}

void dfs2(int x,int f){
	tot++;
	for(int i=g1.last[x];i;i=g1.ne[i]){
		int y=g1.E[i].y;
		if(y==f || vis[y]) continue;
		dfs2(y,x);
	}
}

void solve(int x){
	vis[x]=1;mp1[x][a[x]]=1;
	for(int i=g1.last[x];i;i=g1.ne[i]){
		int y=g1.E[i].y;
		if(vis[y]) continue;
		tot=0,dfs2(y,y);root=0;getroot(y,y);
		fa[root]=x;dfs1(y,y,a[x]+a[y],x,root);
		solve(root);
	}
}

void dfs(int x,int f){
	val[x]=val[f]+a[x];dep[x]=dep[f]+1;anc[x][0]=f;
	for(int i=1;i<=20;i++)anc[x][i]=anc[anc[x][i-1]][i-1];
	for(int i=g1.last[x];i;i=g1.ne[i])if(g1.E[i].y!=f){
		dfs(g1.E[i].y,x);
	}
}

void premake(){
	dfs(1,1);
	tot=n;root=0;
	g[0]=INF;
	getroot(1,1);
	solve(root);
}

int cal(int x,int y){
	int lca=getlca(x,y);
	return val[x]+val[y]-2*val[lca]+a[lca];
}

void make(int x){
	int sum=0,cur=x;
	while(fa[x]){
		int key=0-cal(cur,fa[x])+a[fa[x]];
		sum+=mp1[fa[x]][key]-mp2[x][key];
		x=fa[x];
	}
	dp[cur]=sum+mp1[cur][0];
}

int main(){
	freopen("input","r",stdin);
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		int x;scanf("%d",&x);
		a[i]=x?1:-1;
	}
	for(int i=1;i<n;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		g1.add(x,y);g1.add(y,x);
	}
	for(int i=1;i<=n;i++)scanf("%d",&b[i]);
	premake();int sum=0;
	for(int i=1;i<=n;i++)make(i),sum+=dp[i];
	sum>>=1;int ans=0;
	for(int i=1;i<=n;i++){
		all[i]=all[i-1]+dp[b[i]];
		int l=0,r=i-1,res=-1;
		while(l<=r){
			int mid=(l+r)>>1;
			if(all[i]-all[mid]>sum) res=mid,l=mid+1;
			else r=mid-1;
		}
		ans+=res+1;
	}
	cout<<ans;
	return 0;
}