#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

#define MAXN 10010

int dis[MAXN],n,m,s;
vector <int> to[MAXN];

void bfs(){
	int res=0;
	memset(dis,-1,sizeof(dis));
	queue <int> Q;dis[s]=0,Q.push(s);
	while(!Q.empty()){
		int cur=Q.front();Q.pop();res=max(res,dis[cur]);
		for(int i=0;i<to[cur].size();i++){
			int v=to[cur][i];
			if(dis[v]==-1){
				dis[v]=dis[cur]+1;
				Q.push(v);
			}
		}
	}
	cout<<res+1;
}

int main(){
	freopen("flu.in","r",stdin);
	freopen("flu.ans","w",stdout);
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		static int x,y;
		scanf("%d %d",&x,&y);
		to[x].push_back(y);
		to[y].push_back(x);
	}
	cin>>s;
	bfs();
	return 0;
}