#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define MAXN 100010
#define MAXM 200010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int n,m,last[MAXN],ne[MAXM],edge_cnt;
int size[MAXN],f[MAXN],dis[MAXN],dep[MAXN],root,tot;
int anc[MAXN][25],vis[MAXN],father[MAXN];
vector <int> sum1[MAXN],sum2[MAXN];

struct edge{
	int x,y,z;
}E[MAXM];

void add_edge(int x,int y,int z){
	E[++edge_cnt]=(edge){x,y,z};
	ne[edge_cnt]=last[x];
	last[x]=edge_cnt;
}

void getroot(int x,int fa){
	size[x]=1;f[x]=0;
	for(int i=last[x];i;i=ne[i]){
		if(E[i].y==fa || vis[E[i].y]) continue;
		getroot(E[i].y,x);
		size[x]+=size[E[i].y];
		f[x]=max(f[x],size[E[i].y]);
	}
	f[x]=max(f[x],tot-size[x]);
	if(f[x]<f[root]) root=x;
}

void dfs(int x,int fa){
	tot++;
	for(int i=last[x];i;i=ne[i]){
		if(E[i].y==fa || vis[E[i].y]) continue;
		dfs(E[i].y,x);
	}
}

void make(int x,int fa,int dist,int G1,int G2){
	sum1[G1].push_back(dist);sum2[G2].push_back(dist);
	for(int i=last[x];i;i=ne[i]){
		if(E[i].y==fa || vis[E[i].y]) continue;
		make(E[i].y,x,dist+E[i].z,G1,G2);
	}
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

void solve(int x){
	vis[x]=1;sum1[x].push_back(0);
	for(int i=last[x];i;i=ne[i])if(!vis[E[i].y]){
		tot=0;root=0;dfs(E[i].y,E[i].y);getroot(E[i].y,E[i].y);
		make(E[i].y,E[i].y,E[i].z,x,root);
		father[root]=x;solve(root);
	}
}

void dfs1(int x,int fa,int dist){
	dep[x]=dep[fa]+1;dis[x]=dist;
	anc[x][0]=fa;
	for(int i=1;i<=20;i++)anc[x][i]=anc[anc[x][i-1]][i-1];
	for(int i=last[x];i;i=ne[i])if(E[i].y!=fa){
		dfs1(E[i].y,x,dist+E[i].z);
	}
}

void cal(int x){
	int cur=x,res=-m;
	for(int i=0;i<sum1[x].size();i++) res+=sum1[x][i]^m;
	while(father[x]){
		int dist=dis[cur]+dis[father[x]]-2*dis[lca(cur,father[x])];
		for(int i=0;i<sum2[x].size();i++) res-=(sum2[x][i]+dist)^m;
		for(int i=0;i<sum1[father[x]].size();i++) res+=(sum1[father[x]][i]+dist)^m;
		x=father[x];
	}
	printf("%d\n",res);
}

int main(){
    freopen("warehouse2.in","r",stdin);
    cin>>n>>m;
    for(int i=1;i<n;i++){
    	int x,y,z;
    	scanf("%d %d %d",&x,&y,&z);
    	add_edge(x,y,z);add_edge(y,x,z);
    }
    dfs1(1,1,0);
    tot=n;f[0]=INF;getroot(1,1);solve(root);
    //cout<<cnt2[3]<<endl;
  	for(int i=1;i<=n;i++)cal(i);
    return 0;
}