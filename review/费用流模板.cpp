#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

#define MAXN 5010
#define MAXM 100010

struct edge{
	int x,y,f,w;
}E[MAXM];

int edge_cnt,last[MAXN],ne[MAXM];
int n,m,s,t,ans1,ans2,dis[MAXN],pre[MAXN];
bool instack[MAXN];

void add_edge(int x,int y,int f,int w){
	E[++edge_cnt]=(edge){x,y,f,w};
	ne[edge_cnt]=last[x];
	last[x]=edge_cnt;
}

int spfa(){
	queue <int> Q;int res=1e9;
	memset(instack,0,sizeof(instack));
	memset(dis,0x3f,sizeof(dis));
	instack[s]=true;dis[s]=0;Q.push(s);
	while(!Q.empty()){
		int tp=Q.front();Q.pop();instack[tp]=false;
		for(int i=last[tp];i;i=ne[i]){
			int v=E[i].y;
			if(E[i].f && dis[v]>dis[tp]+E[i].w){
				dis[v]=dis[tp]+E[i].w;pre[v]=i;
				if(!instack[v]){
					instack[v]=true,Q.push(v);
				}
			}
		}
	}
	if(dis[t]==0x3f3f3f3f) return 0;
	for(int i=t;i!=s;i=E[pre[i]].x)
		res=min(res,E[pre[i]].f);
	for(int i=t;i!=s;i=E[pre[i]].x)
		E[pre[i]].f-=res,E[pre[i]^1].f+=res;
	ans2+=res*dis[t];ans1+=res;
	return 1;
}

int main(){
	freopen("input","r",stdin);
	cin>>n>>m>>s>>t;edge_cnt=1;
	for(int i=1;i<=m;i++){
		static int x,y,f,w;
		scanf("%d %d %d %d",&x,&y,&f,&w);
		add_edge(x,y,f,w);
		add_edge(y,x,0,-w);
	}
	while(spfa());
	cout<<ans1<<' '<<ans2;
	return 0;
}
