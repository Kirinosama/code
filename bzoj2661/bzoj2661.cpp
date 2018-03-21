#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <queue>
using namespace std;

#define MAXN 2010
#define MAXM MAXN*MAXN
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int l,r,s,t,ans1,ans2;

struct edge{
	int x,y,z,w;
}E[MAXM];

int ne[MAXM],last[MAXN],edge_cnt,dis[MAXN];
int pre[MAXN];
bool instack[MAXN];

void add_edge(int x,int y,int z,int w){
	E[++edge_cnt]=(edge){x,y,z,w};
	ne[edge_cnt]=last[x];
	last[x]=edge_cnt;
	E[++edge_cnt]=(edge){y,x,0,-w};
	ne[edge_cnt]=last[y];
	last[y]=edge_cnt;
}

int gcd(int x,int y){
	if(!x) return y;
	if(!y) return x;
	return gcd(y,x%y);
}

bool judge(int x,int y){
	if(gcd(x,y)==1){
		int tot=abs(x*x-y*y);
		if(tot==(int)sqrt(tot)*(int)sqrt(tot))
			return true;
	}
	return false;
}

bool spfa(){
	queue <int> Q;
	memset(dis,0xef,sizeof(dis));
	dis[s]=0;instack[s]=true;Q.push(s);
	while(!Q.empty()){
		int tp=Q.front();Q.pop();instack[tp]=false;
		for(int i=last[tp];i;i=ne[i]){
			if(E[i].z && dis[E[i].y]<dis[tp]+E[i].w){
				dis[E[i].y]=dis[tp]+E[i].w;
				pre[E[i].y]=i;
				if(!instack[E[i].y])
					instack[E[i].y]=true,Q.push(E[i].y);
			}
		}
	}
	if(dis[t]==0xefefefef) return false;
	int maxflow=INF,sum=0;
	for(int i=t;i!=s;i=E[pre[i]].x){
		maxflow=min(maxflow,E[pre[i]].z);
		sum+=E[pre[i]].w;
	}
	for(int i=t;i!=s;i=E[pre[i]].x)
		E[pre[i]].z-=maxflow,E[pre[i]^1].z+=maxflow;
	ans1+=maxflow,ans2+=maxflow*sum;
	return true;
}

int main(){
    freopen("bzoj2661.in","r",stdin);
    scanf("%d %d",&l,&r);s=r+r+1,t=s+1;edge_cnt=1;
    for(int i=l;i<=r;i++){
    	add_edge(s,i,1,0);
    	add_edge(i+r,t,1,0);
    	for(int j=i+1;j<=r;j++)
    		if(judge(i,j))
    			add_edge(i,j+r,1,i+j),add_edge(j,i+r,1,i+j);
    }
    while(spfa());
    printf("%d %d",ans1/2,ans2/2);
    return 0;
}