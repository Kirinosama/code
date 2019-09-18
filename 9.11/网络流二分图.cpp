#include <bits/stdc++.h>
using namespace std;

#define MAXN 3010
#define MAXM 100010

int n,m,e;
int last[MAXN],ne[MAXM],edge_cnt;
int s,t,ans,cur[MAXN];

bool bfs(){
	queue<int>Q;
	memset(dis,0x3f,sizeof(dis));
	dis[s]=0;
	Q.push(s);
	while(!Q.empty()){
		int tp=Q.front();
		for(int i=last[x])	
	}
}

int main(){
	freopen("input","r",stdin);
	cin>>n>>m>>e;
	s=n+m+1;t=s+1;
	for(int i=1;i<=e;i++){
		static int x,y;
		scanf("%d%d",&x,&y);
		if(x>n || y>m) continue;
		add_edge(x,y+n,1);
		add_edge(y+n,x,0);
	}
	for(int i=1;i<=n;i++)
		add_edge(s,i,1),add_edge(i,s,0);
	for(int i=1;i<=m;i++)
		add_edge(i+n,t,1),add_edge(t,i+n,0);
	while(bfs()){
		for(int i=1;i<=t;i++)cur[i]=last[i];
		ans+=dinic(s,INF);
	}
	cout<<ans;
	return 0;
}
