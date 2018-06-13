#include <bits/stdc++.h>
using namespace std;

#define MAXN 10010
#define MAXM 50010

int n,m;
int last[MAXN],ne[MAXM],edge_cnt;
int dfn[MAXN],low[MAXN],ti,num[MAXN],col[MAXN],cnt;
int ans,vis[MAXN],ru[MAXN];

stack <int> s;
set <int> to[MAXN];

struct edge{
	int x,y;
}E[MAXM];

void add_edge(int x,int y){
	E[++edge_cnt]=(edge){x,y};
	ne[edge_cnt]=last[x];
	last[x]=edge_cnt;
}

void tarjan(int x){
	s.push(x);
	dfn[x]=low[x]=++ti;
	for(int i=last[x];i;i=ne[i]){
		int y=E[i].y;
		if(!dfn[y]){
			tarjan(y);
			low[x]=min(low[x],low[y]);
		}else{
			low[x]=min(low[x],dfn[y]);
		}
	}
	if(dfn[x]==low[x]){
		int tp=s.top();cnt++;
		while(1){
			col[tp]=cnt;num[cnt]++;
			s.pop();
			if(tp==x) break;
			tp=s.top();
		}
	}
}

int main(){
	freopen("input","r",stdin);
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int x,y;scanf("%d%d",&x,&y);
		add_edge(x,y);
	}
	for(int i=1;i<=n;i++)if(!dfn[i])
		tarjan(i);
	for(int i=1;i<=m;i++)if(col[E[i].x]!=col[E[i].y]){
		if(to[col[E[i].x]].find(col[E[i].y])==to[col[E[i].x]].end()){
			to[col[E[i].x]].insert(col[E[i].y]);
			ru[col[E[i].y]]++;
		}
	}
	queue<int>Q;
	for(int i=1;i<=cnt;i++)vis[i]=1;
	for(int i=1;i<=cnt;i++)if(!ru[i])
		Q.push(i);
	while(!Q.empty()){
		int tp=Q.front();Q.pop();
		for(set<int>::iterator i=to[tp].begin();i!=to[tp].end();i++){
			int y=*i;
			vis[y]+=vis[tp];
			ru[y]--;
			if(!ru[y])Q.push(y);
		}
	}
	for(int i=1;i<=cnt;i++)if(vis[i]==cnt)
		ans+=num[i];
	cout<<ans;
	return 0;
}
