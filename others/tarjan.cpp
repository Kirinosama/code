#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

stack <int> s;
vector <int> t,to[10010];
int n,m,a[10010],f[10010],sum[10010];
int bcc_cnt,cnt,dfn[10010],low[10010],col[10010];
int book[10010],ru[10010],ans;
int last[10010],edge_cnt,pre[100010]; 
bool instack[10010];
int dis[10010];

struct edge{
	int y;
}E[100010];

void add(int x,int y){
	if(x==y) return;
	E[++edge_cnt]=(edge){y};
	pre[edge_cnt]=last[x];
	last[x]=edge_cnt;
}

void tarjan(int u){
	dfn[u]=low[u]=++cnt;
	s.push(u);
	for(int i=0;i<to[u].size();i++){
		int v=to[u][i];
		if(!dfn[v]){
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}else if(!col[v]){
			low[u]=min(low[u],dfn[v]);
		}	
	}	
	if(low[u]==dfn[u]){
		int tp=0;bcc_cnt++;
		while(tp!=u){
			tp=s.top();s.pop();
			col[tp]=bcc_cnt;
		} 
	}
}
/*
int spfa(int s){
	int res=0xc0c0c0c0;
	memset(dis,0xc0,sizeof(dis));
	dis[s]=sum[s];queue<int>Q;
	instack[s]=true;Q.push(s);
	while(!Q.empty()){
		int tp=Q.front();Q.pop();instack[tp]=false;
		res=max(res,dis[tp]);
		for(int i=last[tp];i;i=pre[i]){
			if(dis[E[i].y]<dis[tp]+sum[E[i].y]){
				dis[E[i].y]=sum[E[i].y]+dis[tp];
				if(!instack[E[i].y])Q.push(E[i].y),instack[E[i].y]=true;
			}
		}
	}
	return res;
}
*/
int main(){
	freopen("input","r",stdin);
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<=m;i++){
		static int x,y;
		scanf("%d%d",&x,&y);
		to[x].push_back(y);
	}
	for(int i=1;i<=n;i++){
		if(!dfn[i]) tarjan(i); 
	}
	if(!s.empty()){
		bcc_cnt++;
		while(!s.empty()){
			col[s.top()]=bcc_cnt;
			s.pop();
		}
	}
	for(int i=1;i<=n;i++){
		sum[col[i]]+=a[i];		
		f[col[i]]+=a[i];
		for(int j=0;j<to[i].size();j++)
			add(col[i],col[to[i][j]]);
	}
	for(int i=1;i<=bcc_cnt;i++){
		for(int j=1;j<=bcc_cnt;j++)book[j]=0; 
		for(int j=last[i];j;j=pre[j])
			if(!book[E[j].y]){
				book[E[j].y]=1;
				ru[E[j].y]++;
			}
	} 
	/*
		for(int i=1;i<=bcc_cnt;i++)if(!ru[i])
		ans=max(ans,spfa(i));
	*/
	queue<int>q;
	for(int i=1;i<=bcc_cnt;i++)
		if(!ru[i])q.push(i);
	memset(book,0,sizeof(book));
	while(!q.empty()){
		int cur=q.front();q.pop();
		ans=max(ans,f[cur]);
		for(int i=last[cur];i;i=pre[i])if(!book[E[i].y]){
			ru[E[i].y]--;book[E[i].y]=1;
			if(!ru[E[i].y]) q.push(E[i].y);
			f[E[i].y]=max(f[E[i].y],f[cur]+sum[E[i].y]);
		}
		for(int i=last[cur];i;i=pre[i])book[E[i].y]=0;
	}
	cout<<ans;
	return 0;
}
