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

int s,t,sx,sy,ex,ey,n,m;
int dis[MAXN],last[MAXN],ne[MAXM],edge_cnt;
bool instack[MAXN];
char a[510][510];

struct edge{
	int x,y,z;
}E[MAXM];

void add_edge(int x,int y,int z){
	E[++edge_cnt]=(edge){x,y,z};
	ne[edge_cnt]=last[x];
	last[x]=edge_cnt;
	E[++edge_cnt]=(edge){y,x,z};
	ne[edge_cnt]=last[y];
	last[y]=edge_cnt;
}

int spfa(){
	queue <int> Q;
	memset(dis,0x3f,sizeof(dis));
	dis[s]=0;Q.push(s);instack[s]=true;
	while(!Q.empty()){
		int tp=Q.front();Q.pop();instack[tp]=false;
		for(int i=last[tp];i;i=ne[i]){
			int y=E[i].y;
			if(dis[y]>dis[tp]+E[i].z){
				dis[y]=dis[tp]+E[i].z;
				if(!instack[y]) instack[y]=true,Q.push(y);
			}
		}
	}
	return dis[t];
}

int main(){
	freopen("game.in","r",stdin);
	while(true){
    	cin>>n>>m;
    	if(!n && !m) break;
    	for(int i=0;i<n;i++)scanf("%s",a[i]);
    	scanf("%d %d %d %d",&sx,&sy,&ex,&ey);
    	s=sx*m+sy;t=ex*m+ey;edge_cnt=0;
    	for(int i=0;i<n*m;i++) last[i]=0;
    	for(int i=0;i<n;i++)
    		for(int j=0;j<m;j++){
    			if(i+1<n){
    				if(a[i][j]==a[i+1][j]) add_edge(p(i,j),p((i+1),j),0);
    				else add_edge(p(i,j),p((i+1),j),1);
    			}
    			if(j+1<m){
    				if(a[i][j]==a[i][j+1]) add_edge(p(i,j),p(i,(j+1)),0);
    				else add_edge(p(i,j),p(i,(j+1)),1);
    			}
    		}
    	cout<<spfa()<<endl;
    	//for(int i=0;i<n*m;i++) printf("%d %d\n",i,dis[i]);
    }
	return 0;
}