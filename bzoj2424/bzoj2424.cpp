#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

#define MAXN 60
#define MAXM 1010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int n,m,S,s,t,x,ans,flow,dis[MAXN];
int edge_cnt,last[MAXN],ne[MAXM],pre[MAXN];
bool instack[MAXN];

struct edge{
	int x,y,z,w;
}E[MAXM];

void add_edge(int x,int y,int z,int w){
	E[++edge_cnt]=(edge){x,y,z,w};
	ne[edge_cnt]=last[x];
	last[x]=edge_cnt;
	E[++edge_cnt]=(edge){y,x,0,-w};
	ne[edge_cnt]=last[y];
	last[y]=edge_cnt;
}

bool spfa(){
	queue <int> Q;
	memset(dis,0x3f,sizeof(dis));
	dis[s]=0;instack[s]=true;
	Q.push(s);
	while(!Q.empty()){
		int tp=Q.front();Q.pop();instack[tp]=false;
		for(int i=last[tp];i;i=ne[i]){
			if(E[i].z && dis[tp]+E[i].w<dis[E[i].y]){
				dis[E[i].y]=dis[tp]+E[i].w;
				pre[E[i].y]=i;
				if(!instack[E[i].y])
					instack[E[i].y]=true,Q.push(E[i].y);
			}
		}
	}
	if(dis[t]==INF) return false;
	flow=INF;
	for(int i=t;i!=s;i=E[pre[i]].x)
		flow=min(flow,E[pre[i]].z);
	for(int i=t;i!=s;i=E[pre[i]].x)
		E[pre[i]].z-=flow,E[pre[i]^1].z+=flow;
	ans+=flow*dis[t];
	return true;
}

int main(){
    freopen("bzoj2424.in","r",stdin);
    cin>>n>>m>>S;s=n+1,t=s+1;edge_cnt=1;
    for(int i=1;i<=n;i++){
    	scanf("%d",&x);
    	add_edge(i,t,x,0);
    }
    for(int i=1;i<=n;i++){
    	scanf("%d",&x);
    	add_edge(s,i,INF,x);
    }
    for(int i=1;i<n;i++)
    	add_edge(i,i+1,S,m);
   	while(spfa());
   	printf("%d",ans);
    return 0;
}