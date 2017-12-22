#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

#define MAXN 210
#define MAXM 210

struct edge{
	int x,y,f,w;
}E[MAXM*2];

int n,m,s,t,edge_cnt,ne[MAXM*2],last[MAXN];
int ans1,ans2,back[MAXN],dis[MAXN],instack[MAXN];

void insert(int x,int y,int f,int w){
	E[++edge_cnt]=(edge){x,y,f,w};
	ne[edge_cnt]=last[x];
	last[x]=edge_cnt;
}

void add(int x,int y,int f,int w){
	insert(x,y,f,w),insert(y,x,0,-w);
}

bool spfa()
{
	queue <int> Q;
	memset(dis,0x3f,sizeof(dis));
	memset(instack,0,sizeof(instack));
	instack[s]=1;dis[s]=0;Q.push(s);
	while(!Q.empty()){
		int cur=Q.front();Q.pop();instack[cur]=0;
		for(int i=last[cur];i;i=ne[i]){
			int v=E[i].y;
			if(E[i].f && dis[v]>dis[cur]+E[i].w){
				dis[v]=dis[cur]+E[i].w;
				Q.push(v),instack[v]=true;
				back[v]=i;
			}
		}
	}
	if(dis[t]==0x3f3f3f3f) return false;
	int flow=1e9;
	for(int i=t;i!=s;i=E[back[i]].x){
		flow=min(flow,E[back[i]].f);
	}
	for(int i=t;i!=s;i=E[back[i]].x){
		int num=back[i];
		E[num].f-=flow;E[num^1].f+=flow;
	}
	ans1+=flow;ans2+=flow*dis[t];return true;
}

int main()
{
    freopen("TC12185.in","r",stdin);
    scanf("%d %d",&n,&m);edge_cnt=1;
    for(int i=1;i<=m;i++){
    	static int x,y,f,w;
    	scanf("%d %d %d %d",&x,&y,&f,&w);
    	add(x,y,f,w);
    }
    s=1,t=n;
    while(spfa());
    cout<<ans1<<' '<<ans2;
    return 0;
}