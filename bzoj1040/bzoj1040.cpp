#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 1000010
#define MAXM 2*MAXN
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

ll ans,res,w[MAXN],f[MAXN][2];
ii q[MAXN];
int cnt,n,father[MAXN],ne[MAXM],last[MAXN],edge_cnt;

struct edge{
	int x,y;
}E[MAXM];

int find(int x){
	return father[x]==x?x:father[x]=find(father[x]);
}

void merge(int x,int y){
	int fx=find(x),fy=find(y);
	if(fx!=fy)father[fx]=fy;
}

void add_edge(int x,int y){
	E[++edge_cnt]=(edge){x,y};
	ne[edge_cnt]=last[x];
	last[x]=edge_cnt;
}

void dp(int x,int fa){
	f[x][0]=0,f[x][1]=w[x];
	for(int i=last[x];i;i=ne[i]){
		int y=E[i].y;
		if(y==fa) continue;
		dp(y,x);
		f[x][0]+=max(f[y][0],f[y][1]);
		f[x][1]+=f[y][0];
	}
}

int main(){
    freopen("bzoj1040.in","r",stdin);
    scanf("%d",&n);
    for(int i=1;i<=n;i++) father[i]=i;
    for(int i=1;i<=n;i++){
    	static int x;
    	scanf("%lld %d",&w[i],&x);
    	if(find(i)!=find(x)) add_edge(i,x),add_edge(x,i),merge(i,x);
    	else q[++cnt]=ii(i,x);
    }
    for(int i=1;i<=cnt;i++){
    	int x=q[i].first,y=q[i].second;
    	dp(x,x);res=f[x][0];
    	dp(y,y);res=max(res,f[y][0]);
    	ans+=res;
    }
    printf("%lld",ans);
    return 0;
}