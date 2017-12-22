#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

#define MAXN 1010
#define MAXM 20010

int back[MAXN],instack[MAXN],dis[MAXN],ne[MAXM*4],last[MAXN];
int n,m,s,t,ans,edge_cnt;

struct edge
{
	int x,y,f,w;
}E[MAXM*4];

void insert(int x,int y,int f,int w)
{
	E[++edge_cnt]=(edge){x,y,f,w};
	ne[edge_cnt]=last[x];
	last[x]=edge_cnt;
}

void add_edge(int x,int y,int f,int w)
{
	insert(x,y,f,w);
	insert(y,x,0,-w);
}

int spfa()
{
	queue <int> Q;int res=0;int flow=0x3f3f3f3f;
	memset(dis,0x7f,sizeof(dis));	
	memset(instack,0,sizeof(instack));
	dis[s]=0;Q.push(s);instack[s]=1;
	while(!Q.empty())
	{
		int cur=Q.front();Q.pop();instack[cur]=0;
		for(int i=last[cur];i;i=ne[i])
		{
			int v=E[i].y;
			if(E[i].f && dis[v]>dis[cur]+E[i].w)
			{
				back[v]=i;dis[v]=dis[cur]+E[i].w;
				instack[v]=1;Q.push(v);
			}
		}
	}
	if(dis[t]==0x7f7f7f7f) return 0;
	for(int i=t;i!=s;i=E[back[i]].x)
		flow=min(flow,E[back[i]].f);
	for(int i=t;i!=s;i=E[back[i]].x)
	{
		int cur=back[i];
		E[cur].f-=flow;E[cur^1].f+=flow;
	}
	return dis[t]*flow;
}

int main()
{
    freopen("TC12184.in","r",stdin);
 	cin>>n>>m;edge_cnt=1;
 	for(int i=1;i<=m;i++){
 		static int x,y,z;
 		scanf("%d %d %d",&x,&y,&z);
 		add_edge(x,y,1,z);
 		add_edge(y,x,1,z);
 	}
 	s=n+1,t=s+1;
 	add_edge(s,1,2,0);add_edge(n,t,2,0);
 	while(int tans=spfa()) 	ans+=tans;
 	cout<<ans;
 	return 0;
}