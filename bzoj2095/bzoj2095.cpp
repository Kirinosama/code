#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

#define MAXN 1010
#define MAXM 2020

int n,m,ans,l,r,s,t,dis[MAXN],father[MAXN];
int ru[MAXN],chu[MAXN],last[MAXN],cur[MAXN],ne[MAXN*7],edge_cnt;

struct edge{
	int a,b,c,d;
}E[MAXM];

struct bian{
	int x,y,z;
}to[MAXN*7];

void add_edge(int x,int y,int z){
	to[++edge_cnt]=(bian){x,y,z};
	ne[edge_cnt]=last[x];
	last[x]=edge_cnt;
	to[++edge_cnt]=(bian){y,x,0};
	ne[edge_cnt]=last[y];
	last[y]=edge_cnt;
}

bool bfs(){
	queue <int> Q;
	memset(dis,0,sizeof(dis));
	dis[s]=1,Q.push(s);
	while(!Q.empty()){
		int tp=Q.front();Q.pop();
		if(tp==t) return true;
		for(int i=last[tp];i;i=ne[i]){
			int y=to[i].y;
			if(!dis[y] && to[i].z){
				dis[y]=dis[tp]+1;
				Q.push(y);
			}
		}
	}
	return false;
}

int dinic(int x,int tot){
	int sum=0;int k;
	if(x==t) return tot;
	for(int i=last[x];i;i=ne[i]){
		int y=to[i].y;
		if(to[i].z && dis[y]==dis[x]+1 && (k=dinic(y,min(to[i].z,tot-sum)))){
			sum+=k,to[i].z-=k,to[i^1].z+=k;
			if(sum==tot) return sum;
		}
	}
	if(!sum) dis[x]=0;
	return sum;
}

int find(int x){
	return father[x]==x?x:father[x]=find(father[x]);
}

void merge(int x,int y){
	int fx=find(x),fy=find(y);
	if(fx!=fy) father[fx]=fy;
}

bool judge(int val){
	for(int i=1;i<=n;i++) father[i]=i;
	for(int i=1;i<=m;i++)
		if(E[i].c<=val || E[i].d<=val)
			merge(E[i].a,E[i].b);
	for(int i=1;i<n;i++) if(find(i)!=find(i+1)) return false;
	memset(last,0,sizeof(last));edge_cnt=1;
	memset(ru,0,sizeof(ru)),memset(chu,0,sizeof(chu));
	for(int i=1;i<=m;i++){
		if(E[i].c<=val && E[i].d<=val){
			chu[E[i].a]++,ru[E[i].b]++;
			add_edge(E[i].b,E[i].a,1);
		}
		else if(E[i].c<=val)
			chu[E[i].a]++,ru[E[i].b]++;
		else 
			chu[E[i].b]++,ru[E[i].a]++;
	}
	int tot=0;
	for(int i=1;i<=n;i++){
		if((ru[i]&1)!=(chu[i]&1))
			return false;
		if(ru[i]>=chu[i]) add_edge(s,i,(ru[i]-chu[i])/2),tot+=(ru[i]-chu[i])/2; 
		else add_edge(i,t,(chu[i]-ru[i])/2);
	}
	int sum=0;
	while(bfs()){
		for(int i=1;i<=t;i++) cur[i]=last[i];
		sum+=dinic(s,1e9);
	}
	if(sum==tot) return true;
	else return false;
}

int main(){
	freopen("inout","r",stdin);
	scanf("%d %d",&n,&m);s=n+1,t=s+1;
	for(int i=1;i<=m;i++){
		scanf("%d %d %d %d",&E[i].a,&E[i].b,&E[i].c,&E[i].d);
		l=max(l,min(E[i].c,E[i].d));
		r=max(r,max(E[i].c,E[i].d));
	}
	while(l<=r){
		int mid=(l+r)>>1;
		if(judge(mid)) ans=mid,r=mid-1;
		else l=mid+1;
	}
	if(!ans) printf("NIE");
	else printf("%d",ans);
	return 0;
}
