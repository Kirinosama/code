#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define MAXN 100010

vector <int> to[MAXN];
int n,m,ti,root,dfn[MAXN],low[MAXN],ans;
bool book[MAXN];

void tarjan(int u,int fa){
	dfn[u]=low[u]=++ti;
	int child=0;
	for(int i=0;i<to[u].size();i++){
		int v=to[u][i];
		if(!dfn[v]){
			tarjan(v,fa);
			low[u]=min(low[u],low[v]);
			if(low[v]>=dfn[u] && u!=fa) book[u]=true;
			if(u==fa) child++;
		}
		else low[u]=min(low[u],dfn[v]);
	}
	if(fa==u && child>=2) book[u]=true;
}

int main(){
	freopen("input","r",stdin);
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		static int x,y;
		scanf("%d %d",&x,&y);
		to[x].push_back(y);
		to[y].push_back(x);
	}
	for(int i=1;i<=n;i++)
		if(!dfn[i]) tarjan(i,i);
	for(int i=1;i<=n;i++)
		if(book[i]) ans++;
	cout<<ans<<endl;
	for(int i=1;i<=n;i++)
		if(book[i]) cout<<i<<' ';
	return 0;
}