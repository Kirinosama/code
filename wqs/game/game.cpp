#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

#define p(x,y) (x*m+y)
#define MAXN 250010
#define MAXM MAXN*4
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int s,t,sx,sy,ex,ey,n,m,fa[MAXN];
int dis[MAXN],last[MAXN],ne[MAXM],edge_cnt;
char a[510][510];

struct edge{
	int x,y;
}E[MAXM];

void add_edge(int x,int y){
	E[++edge_cnt]=(edge){x,y};
	ne[edge_cnt]=last[x];
	last[x]=edge_cnt;
	E[++edge_cnt]=(edge){y,x};
	ne[edge_cnt]=last[y];
	last[y]=edge_cnt;
}

int find(int x){
	return fa[x]==x?x:fa[x]=find(fa[x]);
}

void merge(int x,int y){
	int fx=find(x),fy=find(y);
	if(fx!=fy) fa[fx]=fy;
}

int bfs(int x,int y){
	queue <int> Q;
	memset(dis,0x3f,sizeof(dis));
	dis[x]=0;Q.push(x);
	while(!Q.empty()){
		int tp=Q.front();Q.pop();
		for(int i=last[tp];i;i=ne[i])if(dis[E[i].y]==INF){
			dis[E[i].y]=dis[tp]+1;
			Q.push(E[i].y);
			if(E[i].y==y) return dis[y];
		}
	}
	return 0;
}

int main(){
    freopen("game.in","r",stdin);
    freopen("game.out","w",stdout);
    while(true){
    	cin>>n>>m;
    	if(n==0 && m==0) break;
    	for(int i=0;i<n;i++)scanf("%s",a[i]);
    	scanf("%d %d %d %d",&sx,&sy,&ex,&ey);
    	s=sx*m+sy;t=ex*m+ey;
    	for(int i=0;i<n*m;i++) fa[i]=i;
    	for(int i=0;i<n;i++)
    		for(int j=0;j<m;j++){
    			if(i+1<n && a[i][j]==a[i+1][j]) merge(p(i,j),p((i+1),j));
    			if(j+1<m && a[i][j]==a[i][j+1]) merge(p(i,j),p(i,(j+1)));
    		}
    	edge_cnt=0;
    	for(int i=0;i<n*m;i++) last[i]=0;
    	for(int i=0;i<n;i++)
    		for(int j=0;j<m;j++){
    			if(i+1<n && a[i][j]!=a[i+1][j]) add_edge(find(p(i,j)),find(p((i+1),j)));
    			if(j+1<m && a[i][j]!=a[i][j+1]) add_edge(find(p(i,j)),find(p(i,(j+1))));
    		}
    	printf("%d\n",bfs(find(s),find(t)));
    }
    return 0;
}