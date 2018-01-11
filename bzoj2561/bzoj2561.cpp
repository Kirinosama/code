#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

#define MAXN 20010
#define MAXM 800010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

struct edge{
	int x,y,z;
}e[MAXM],E[MAXM];

int last[MAXN],cur[MAXN],ne[MAXM],edge_cnt;
int ans,n,m,u,v,k,dis[MAXN];

bool cmp(const edge &a,const edge &b){
	return a.z<b.z;
}

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
	dis[u]=1;Q.push(u);
	while(!Q.empty()){
		int tp=Q.front();Q.pop();
		if(tp==v) return true;
		for(int i=last[tp];i;i=ne[i]){
			int y=E[i].y;
			if(E[i].z && !dis[y])
				dis[y]=dis[tp]+1,Q.push(y);
		}
	}
	return false;
}

int maxflow(int x,int tot){
	int sum=0,p=0;
	if(x==v) return tot;
	for(int &i=cur[x];i;i=ne[i]){
		int y=E[i].y;
		if(E[i].z && dis[y]==dis[x]+1 && (p=maxflow(y,min(tot-sum,E[i].z)))){
			E[i].z-=p,E[i^1].z+=p,sum+=p;
			if(tot==sum) return sum;
		}
	}
	if(!sum) dis[x]=0;
	return sum;
}

int main(){
    freopen("bzoj2561.in","r",stdin);
    scanf("%d %d",&n,&m);
    for(int i=1;i<=m;i++)
    	scanf("%d %d %d",&e[i].x,&e[i].y,&e[i].z);
    scanf("%d %d %d",&u,&v,&k);
    sort(e+1,e+1+m,cmp);edge_cnt=1;
    for(int i=1;i<=m && e[i].z<k;i++){
    	add_edge(e[i].x,e[i].y,1);
    	add_edge(e[i].y,e[i].x,1);
    }
    while(bfs()){
    	for(int i=1;i<=n;i++)
    		cur[i]=last[i];
    	ans+=maxflow(u,INF);
    }
    edge_cnt=1;
    memset(last,0,sizeof(last));
    for(int i=m;i>=1 && e[i].z>k;i--){
    	add_edge(e[i].x,e[i].y,1);
    	add_edge(e[i].y,e[i].x,1);
    }
    while(bfs()){
    	for(int i=1;i<=n;i++)
    		cur[i]=last[i];
    	ans+=maxflow(u,INF);
    }
    printf("%d",ans);
    return 0;
}