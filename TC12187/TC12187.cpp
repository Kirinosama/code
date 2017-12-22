#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

#define MAXN 210
#define MAXM 2010
#define INF 1e9

struct edge{
	int x,y,f;
}E[MAXM];

int n,m,s,t,edge_cnt,ne[MAXM*2],last[MAXN];
int cur[MAXN],dis[MAXN],ans;

void insert (int x,int y,int f){
	E[++edge_cnt]=(edge){x,y,f};
	ne[edge_cnt]=last[x];
	last[x]=edge_cnt;
}

void add(int x,int y,int f){
	insert(x,y,f),insert(y,x,0);
}

bool bfs(){
	queue <int> Q;
	memset(dis,0,sizeof(dis));
	while(!Q.empty()) Q.pop();
	dis[s]=1;Q.push(s);
	while(!Q.empty()){
		int x=Q.front();Q.pop();
		if(x==t) return true;
		for(int i=last[x];i;i=ne[i]){
			int y=E[i].y;
			if(!dis[y] && E[i].f){
				dis[y]=dis[x]+1;
				Q.push(y);
			}
		}
	}
	return false;
}

int dinic(int x,int flow){
	int res=0;
	if(x==t) return flow;
	for(int &i=cur[x];i;i=ne[i]){
		int y=E[i].y;
		if(E[i].f && dis[y]==dis[x]+1){
			int k=dinic(y,min(flow-res,E[i].f));
			res+=k,E[i].f-=k,E[i^1].f+=k;
			if(res==flow) return flow;
		}
	}
	if(res==0) dis[x]=0;
	return res;
}

int main()
{
    freopen("TC12187.in","r",stdin);
    scanf("%d\n",&m);edge_cnt=1;s='A',t='Z';
    for(int i=1;i<=m;i++){
    	static char x,y;
    	static int z;
    	scanf("%c %c %d\n",&x,&y,&z);
    	n=max(n,(int)x);n=max(n,(int)y);
    	add(x,y,z);
    	add(y,x,z);
    }
    while(bfs()){
    	for(int i=1;i<=n;i++) cur[i]=last[i];
    	ans+=dinic(s,INF);
    }
    cout<<ans;
    return 0;
}