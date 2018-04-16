#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
#include <set>
using namespace std;

#define INF 0x3f3f3f3f
#define MAXN 10010
#define MAXM 18000

struct edge{
	int x,y,z;
}E[MAXM];

int last[MAXN],ne[MAXM],edge_cnt;
int dis[MAXN],col[MAXN],cur[MAXN];
int n,m,ans,a[MAXN],b[MAXN],c[MAXN];
set <int> S;

void add_edge(int x,int y,int z){
	E[++edge_cnt]=(edge){x,y,z};
	ne[edge_cnt]=last[x];
	last[x]=edge_cnt;
	E[++edge_cnt]=(edge){y,x,z};
	ne[edge_cnt]=last[y];
	last[y]=edge_cnt;
}

void reset(){
	for(int i=1;i<edge_cnt;i++){
		E[i].z=E[i^1].z=(E[i].z+E[i^1].z)>>1;
	}
}

int dfs(int x,int sum,int t){
	if(x==t) return sum;
	int tot=0,k;
	for(int &i=cur[x];i;i=ne[i]){
		if(E[i].z && dis[E[i].y]==dis[x]+1 && (k=dfs(E[i].y,min(sum-tot,E[i].z),t)))
			E[i].z-=k,E[i^1].z+=k,tot+=k;
		if(tot==sum) return tot;
	}
	if(!tot) dis[x]=-1;
	return tot;
}

bool bfs(int s,int t){
	queue<int>Q;Q.push(s);
	memset(dis,-1,sizeof(dis));
	dis[s]=0;
	while(!Q.empty()){
		int tp=Q.front();Q.pop();
		for(int i=last[tp];i;i=ne[i])if(E[i].z && dis[E[i].y]==-1)
			dis[E[i].y]=dis[tp]+1,Q.push(E[i].y);
	}
	return dis[t]!=-1;
}

int dinic(int s,int t){
	reset();int res=0;
	while(bfs(s,t)){
		for(int i=1;i<=n;i++)cur[i]=last[i];
		res+=dfs(s,INF,t);
	}
	return res;
}

void paint(int x){
	col[x]=1;
	for(int i=last[x];i;i=ne[i])if(E[i].z && !col[E[i].y])
		paint(E[i].y);
}

void solve(int l,int r){
	if(l==r) return;
	int s=a[l],t=a[r];
	int mincut=dinic(s,t),i=0,j=0;
	if(S.find(mincut)==S.end()) ans++,S.insert(mincut);
	memset(col,0,sizeof(col));
	paint(s);
	for(int k=l;k<=r;k++){
		if(col[a[k]]) b[++i]=a[k];
		else c[++j]=a[k];
	}
	for(int k=1;k<=i;k++)a[l+k-1]=b[k];
	for(int k=1;k<=j;k++)a[l+i-1+k]=c[k];
	solve(l,l+i-1);solve(l+i,r);
}

int main(){
	freopen("bzoj4519.in","r",stdin);
	cin>>n>>m;edge_cnt=1;
	for(int i=1;i<=m;i++){
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		add_edge(x,y,z);
	}
	for(int i=1;i<=n;i++)a[i]=i;
	solve(1,n);
	cout<<ans;
	return 0;
}
