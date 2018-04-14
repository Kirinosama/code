#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

#define MAXN 60
#define MAXM 5010
#define INF 0x3f3f3f3f
int n,a1,a2,an,b1,b2,bn;
int s,t,last[120],edge_cnt,ne[MAXM];
int cur[MAXN],dis[MAXN];
char c[60][60];

struct edge{
	int x,y,z;
}E[MAXM];

void add_edge(int x,int y,int z){
	E[++edge_cnt]=(edge){x,y,z};
	ne[edge_cnt]=last[x];
	last[x]=edge_cnt;
	E[++edge_cnt]=(edge){y,x,0};
	ne[edge_cnt]=last[y];
	last[y]=edge_cnt;
}

void init(){
	memset(last,0,sizeof(last));edge_cnt=1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(c[i][j]=='O') add_edge(i,j,2);
			if(c[i][j]=='N') add_edge(i,j,INF);
		}
	}
}

bool bfs(){
	queue <int> Q;
	memset(dis,-1,sizeof(dis));
	dis[s]=0;Q.push(s);
	while(!Q.empty()){
		int tp=Q.front();Q.pop();
		for(int i=last[tp];i;i=ne[i])if(E[i].z){
			if(dis[E[i].y]==-1) dis[E[i].y]=dis[tp]+1,Q.push(E[i].y);
		}
	}
	return dis[t]!=-1;
}

int dinic(int x,int tot){
	int sum=0,k;
	if(x==t) return tot;
	for(int &i=cur[x];i;i=ne[i]){
		if(E[i].z && dis[E[i].y]==dis[x]+1 && (k=dinic(E[i].y,min(tot-sum,E[i].z)))){
			E[i].z-=k,E[i^1].z+=k,sum+=k;
			if(sum==tot) return sum;
		}
	}
	if(!sum) dis[x]=-1;
	return sum;
}

int maxflow(){
	int res=0;
	while(bfs()){
		for(int i=1;i<=t;i++)cur[i]=last[i];
		res+=dinic(s,INF);
	}
	return res;
}

int main(){
	freopen("bzoj3504.in","r",stdin);
	while(cin>>n>>a1>>a2>>an>>b1>>b2>>bn){
		a1++,a2++,b1++,b2++;
		s=n+1,t=s+1;
		for(int i=1;i<=n;i++){
			scanf("\n");
			for(int j=1;j<=n;j++)
				scanf("%c",&c[i][j]);
		}
		init();
		add_edge(s,a1,an*2);add_edge(a2,t,an*2);
		add_edge(s,b1,bn*2);add_edge(b2,t,bn*2);
		if(maxflow()>=(an+bn)*2){
			init();		
			add_edge(s,a1,an*2);add_edge(a2,t,an*2);
			add_edge(s,b2,bn*2);add_edge(b1,t,bn*2);
			printf("%s\n",maxflow()>=(an+bn)*2?"Yes":"No");
		}else cout<<"No"<<endl;
	}
	return 0;
}
