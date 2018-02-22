#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

#define MAXN 1510
#define MAXM 2000000
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

struct edge{
	int x,y,z;
}E[MAXM];

struct node{
	int ID,c;
	bool operator < (const node &a)const{
		return c<a.c;
	}
}p[MAXN];

int last[MAXN],ne[MAXM],edge_cnt,n,ans;
int cur[MAXN],dis[MAXN],f[MAXN],s,t,T;
int a[MAXN],b[MAXN],anss[MAXN];

void add_edge(int x,int y,int z){
	E[++edge_cnt]=(edge){x,y,z};
	ne[edge_cnt]=last[x];
	last[x]=edge_cnt;
	E[++edge_cnt]=(edge){y,x,0};
	ne[edge_cnt]=last[y];
	last[y]=edge_cnt;
}

bool bfs(){
	queue <int> Q;
	memset(dis,0,sizeof(dis));
	dis[s]=1;Q.push(s);
	while(!Q.empty()){
		int tp=Q.front();Q.pop();
		for(int i=last[tp];i;i=ne[i])if(E[i].z){
			if(!dis[E[i].y]){
				dis[E[i].y]=dis[tp]+1;
				Q.push(E[i].y);
			}
		}
	}
	if(dis[t]) return true;
	else return false;
}

int dinic(int x,int tot){
	int sum=0,k;
	if(x==t) return tot;
	for(int &i=cur[x];i;i=ne[i])if(E[i].z){
		int y=E[i].y;
		if(dis[y]==dis[x]+1 && (k=dinic(y,min(tot-sum,E[i].z)))){
			E[i].z-=k,E[i^1].z+=k,sum+=k;
			if(sum==tot) return sum;
		}
	}
	if(!sum) dis[x]=0;
	return sum;
}

void solve(){
	int ans=0,maxflow=0,anscnt=0;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)scanf("%d",&b[i]);
	for(int i=1;i<=n;i++){
		int x;scanf("%d",&x);
		p[i]=(node){i,x};
	}
	sort(p+1,p+n+1);
	edge_cnt=1;s=2*n+1,t=s+1;
	memset(last,0,sizeof(last));
	memset(f,0,sizeof(f));
	for(int i=1;i<=n;i++){
		f[i]=1;
		for(int j=1;j<i;j++)if(a[j]<a[i])
			f[i]=max(f[i],f[j]+1);
		ans=max(ans,f[i]);
	}
	for(int i=1;i<=n;i++) add_edge(i,i+n,b[i]);
	for(int i=1;i<=n;i++){
		if(f[i]==1) add_edge(s,i,INF);
		if(f[i]==ans) add_edge(i+n,t,INF);
		for(int j=1;j<i;j++)if(a[j]<a[i] && f[j]==f[i]-1)
			add_edge(j+n,i,INF);
	}
	while(bfs()){
		for(int i=1;i<=t;i++) cur[i]=last[i];
		maxflow+=dinic(s,INF);
	}
	for(int i=1;i<=n;i++){
		int pos=p[i].ID,tmp;
		for(int j=last[pos];j;j=ne[j])if(E[j].y==pos+n){
			tmp=j;break;
		}
		if(!E[tmp].z){
			s=pos,t=pos+n;
			if(!bfs()){
				anss[++anscnt]=pos;
				s=pos,t=2*n+1;
				while(bfs()){
					for(int i=1;i<=2*n+2;i++) cur[i]=last[i];
					dinic(s,INF);
				}
				s=2*n+2,t=pos+n;
				while(bfs()){
					for(int i=1;i<=2*n+2;i++) cur[i]=last[i];
					dinic(s,INF);
				}
				E[tmp].z=E[tmp^1].z=0;
			}
		}
	}
	printf("%d %d\n",maxflow,anscnt);
	sort(anss+1,anss+anscnt+1);
	for(int i=1;i<=anscnt;i++){
		printf("%d",anss[i]);
		if(i!=anscnt) printf(" ");
	}
	if(T!=0) cout<<endl;
}

int main(){
    freopen("bzoj3532.in","r",stdin);
   	scanf("%d",&T);
   	while(T--) solve();
    return 0;
}