#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

#define MAXN 1010
#define MAXM 20100
#define INF 1e9

struct edge{
	int x,y,f;
}E[MAXM*2];

int n,a,b,s,t,edge_cnt,ne[MAXM*2],last[MAXN];
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
    freopen("TC12188.in","r",stdin);
    scanf("%d %d %d",&n,&a,&b);
    edge_cnt=1;s=2*n+a+b+1;t=s+1;
    for(int i=1;i<=n;i++)
    	static int x,y,z;
    	scanf("%d %d",&x,&y);
    	for(int i=1;i<=x;i++) scanf("%d",&z),add(2*n+z,i,1);
    	for(int i=1;i<=y;i++) scanf("%d",&z),add(i+n,2*n+a+z,1);
    	add(i,i+n,1);
    }
    for(int i=2*n+1;i<=2*n+a;i++) add(s,i,1);
    for(int i=2*n+a+1;i<=2*n+a+b;i++) add(i,t,1); 
    while(bfs()){
    	for(int i=1;i<=t;i++) cur[i]=last[i];
    	ans+=dinic(s,INF);
    }
    cout<<ans;
    return 0;
}