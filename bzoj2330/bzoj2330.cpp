#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

#define MAXN 200010
#define MAXM 2*MAXN
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int n,book[MAXN],dis[MAXN],k,s,r,a,b;
int last[MAXN],ne[MAXM],edge_cnt;
bool instack[MAXN];

struct edge{
	int x,y,z;
}E[MAXM];

void add_edge(int x,int y,int z){
	E[++edge_cnt]=(edge){x,y,z};
	ne[edge_cnt]=last[x];
	last[x]=edge_cnt;
}

void spfa(){
	ll ans=0;
	queue <int> Q;
	for(int i=1;i<=n;i++){
		Q.push(i),book[i]=1;
		dis[i]=1,instack[i]=true;
	}
	while(!Q.empty()){
		int tp=Q.front();Q.pop();instack[tp]=false;
		if(book[tp]>=n){
			printf("-1");
			return;
		}
		for(int i=last[tp];i;i=ne[i]){
			int y=E[i].y;
			if(dis[y]<dis[tp]+E[i].z){
				dis[y]=dis[tp]+E[i].z;
				if(!instack[y])
					instack[y]=true,book[y]++,Q.push(y);
			}
		}
	}
	for(int i=1;i<=n;i++)
		ans+=dis[i];
	printf("%lld",ans);
}

int main(){
    freopen("bzoj2330.in","r",stdin);
    scanf("%d %d",&n,&k);
    for(int i=1;i<=k;i++){
    	scanf("%d %d %d",&r,&a,&b);
    	if(r==1) add_edge(a,b,0),add_edge(b,a,0);
    	if(r==2){
    		if(a==b){
    			printf("-1");
    			return 0;
    		}
    		add_edge(a,b,1);
    	}
    	if(r==3) add_edge(b,a,0);
    	if(r==4){
    		if(a==b){
    			printf("-1");
    			return 0;
    		}
    		add_edge(b,a,1);
    	}
    	if(r==5) add_edge(a,b,0);
    }
    spfa();
    return 0;
}