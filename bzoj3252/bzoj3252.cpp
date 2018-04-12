#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define MAXN 200010
#define MAXM 400010
typedef long long ll;

struct edge{
	int x,y;
}E[MAXM];

int last[MAXN],ne[MAXM],edge_cnt;
int n,k,top[MAXN],fa[MAXN],son[MAXN];
ll val[MAXN],maxval[MAXN];

void add_edge(int x,int y){
	E[++edge_cnt]=(edge){x,y};
	ne[edge_cnt]=last[x];
	last[x]=edge_cnt;
}

void dfs1(int x,int f){
	maxval[x]=val[x];fa[x]=f;
	for(int i=last[x];i;i=ne[i])if(E[i].y!=f){
		dfs1(E[i].y,x);
		if(maxval[E[i].y]>maxval[son[x]]) son[x]=E[i].y;
		maxval[x]=max(maxval[x],val[x]+maxval[E[i].y]);
	}
}

void dfs2(int x,int tp){
	top[x]=tp;
	if(son[x]) dfs2(son[x],tp);
	for(int i=last[x];i;i=ne[i])if(E[i].y!=fa[x] && E[i].y!=son[x]){
		dfs2(E[i].y,E[i].y);
	}
}

int main(){
	freopen("bzoj3252.in","r",stdin);
	cin>>n>>k;
	for(int i=1;i<=n;i++)scanf("%lld",&val[i]);
	for(int i=1;i<n;i++){
		int x,y;scanf("%d%d",&x,&y);
		add_edge(x,y);add_edge(y,x);
	}
	dfs1(1,1);
	dfs2(1,1);
	vector <ll> s;
	for(int i=1;i<=n;i++)if(top[i]==i){
		s.push_back(maxval[i]);
	}
	sort(s.begin(),s.end());ll ans=0;
	for(int i=(int)s.size()-1;i>=0 && k;i--,k--){
		ans+=s[i];
	}
	cout<<ans;
	return 0;
}
