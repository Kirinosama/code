#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

#define MAXN 50010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int n,m,ans,dis[MAXN];
vector <int> to[MAXN];

void link(int x,int y){
	to[x].push_back(y);
	to[y].push_back(x);
}

void init(){
	int k,x,y;
	for(int i=1;i<=n;i++)
		to[i].clear();
	for(int i=1;i<=m;i++){
		scanf("%d",&k);y=0;
		for(int j=1;j<=k;j++){
			scanf("%d",&x);
			if(y) link(x,y);
			y=x;
		}
	}
}

void bfs(int s){
	queue <int> Q;
	memset(dis,0x3f,sizeof(dis));
	dis[s]=0;Q.push(s);
	while(!Q.empty()){
		int tp=Q.front();Q.pop();
		ans=max(ans,dis[tp]);
		for(int i=0;i<to[tp].size();i++)
			if(dis[to[tp][i]]>dis[tp]+1)
				dis[to[tp][i]]=dis[tp]+1,Q.push(to[tp][i]);
	}
}

int main(){
    freopen("bzoj1023.in","r",stdin);
    freopen("out3","w",stdout);
   	while(scanf("%d %d",&n,&m)!=EOF){
   		init();ans=0;
   		for(int i=1;i<=n;i++)bfs(i);
   		cout<<ans<<endl;
   	}
    return 0;
}