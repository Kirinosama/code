#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 210
#define MAXQ 50010
#define INF 0x3f3f3f3f

struct query{
	int x,y,t;
}Q[MAXQ];

int cur,n,m,t,a[MAXN],e[MAXN][MAXN],dis[MAXN][MAXN];

void solve(int x,int y,int z){
	cout<<((dis[x][y]==INF || a[x]>z || a[y]>z) ? -1 : dis[x][y])<<endl; 
}

void change(int x){
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			dis[i][j]=min(dis[i][j],dis[i][x]+dis[x][j]);
}

int main(){
	freopen("input","r",stdin);
	cin>>n>>m;memset(dis,0x3f,sizeof(dis));
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		dis[i][i]=0;
	}
	for(int i=1;i<=m;i++){
		int x,y,k;
		scanf("%d %d %d",&x,&y,&k);
		x++,y++;
		dis[x][y]=dis[y][x]=k;
	}
	cin>>t;
	for(int i=1;i<=t;i++){
		int x,y,k;
		scanf("%d %d %d",&x,&y,&k);
		Q[i]=(query){++x,++y,k};
	}
	cur=1;
	for(int i=1;i<=n;i++){
		while(Q[cur].t<a[i]){
			solve(Q[cur].x,Q[cur].y,Q[cur].t);
			cur++;
		}
		change(i);
	}
	while(cur<=t){
		solve(Q[cur].x,Q[cur].y,Q[cur].t);
		cur++;
	}
	return 0;
}