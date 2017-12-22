#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

#define MAXN 10010
#define MAXM 100010
#define INF 0x3f3f3f3f

struct edge{
	int x,y,f;
}E[MAXM*2];

int edge_cnt,last[MAXN],ne[MAXM*2];
int n,m,s,t,dis[MAXN],ans,cur[MAXN];

void add_edge(int x,int y,int f){
	E[++edge_cnt]=(edge){x,y,f};
	ne[edge_cnt]=last[x];
	last[x]=edge_cnt;
}

int bfs(){
	queue<int> Q;
	memset(dis,-1,sizeof(dis));
	Q.push(s);dis[s]=0;
	while(!Q.empty()){
		int tp=Q.front();Q.pop();
		if(tp==t) return 1;
		for(int i=last[tp];i;i=ne[i]){
			int v=E[i].y;
			if(dis[v]==-1 && E[i].f){
				dis[v]=dis[tp]+1;
				Q.push(v);
			}
		}
	}
	return 0;
}

int dinic(int x,int flow){
	int sum=0;
	if(x==t) return flow;
	for(int &i=cur[x];i;i=ne[i]){
		int v=E[i].y;
		if(E[i].f && dis[v]==dis[x]+1){
			int p=dinic(v,min(flow-sum,E[i].f));
			sum+=p,E[i].f-=p,E[i^1].f+=p;
			if(sum==flow) return sum;
		}
	}
	if(!sum) dis[x]=-1;
	return sum;
}

int main(){
	freopen("input","r",stdin);
	cin>>n>>m>>s>>t;edge_cnt=1;
	for(int i=1;i<=m;i++){
		static int x,y,k;
		scanf("%d %d %d",&x,&y,&k);
		add_edge(x,y,k);
		add_edge(y,x,0);
	}
	while(bfs()){
		for(int i=1;i<=n;i++) cur[i]=last[i];
		ans+=dinic(s,INF);
	}
	cout<<ans;
	return 0;
}