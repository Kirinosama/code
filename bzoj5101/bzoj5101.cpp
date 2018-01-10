#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MOD 1000000007
#define cnt(x,y) ((x-1)*m+y)
#define MAXM 1000010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

struct edge{
	int x,y;
	ll z;
}E[MAXM];

int n,m,h,edge_cnt,father[MAXM];
ll f[MAXM],g[MAXM],x;

bool cmp(const edge &a,const edge &b){
	return a.z<b.z;
}

int find(int x){
	return father[x]==x?x:father[x]=find(father[x]);
}

int main(){
    freopen("bzoj5101.in","r",stdin);
    scanf("%d %d %d",&n,&m,&h);
    for(int i=1;i<=n;i++)
    	for(int j=1;j<m;j++){
    		scanf("%lld",&x);
    		E[++edge_cnt]=(edge){cnt(i,j),cnt(i,j+1),x};
    	}
	for(int i=1;i<n;i++)
		for(int j=1;j<=m;j++){
			scanf("%lld",&x);
			E[++edge_cnt]=(edge){cnt(i,j),cnt(i+1,j),x};
		}
	sort(E+1,E+1+edge_cnt,cmp);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			father[cnt(i,j)]=cnt(i,j);
			g[cnt(i,j)]=0,f[cnt(i,j)]=1;
		}
	for(int i=1;i<=edge_cnt;i++){
		int u=E[i].x,v=E[i].y;
		int fx=find(u),fy=find(v);
		if(fx==fy) continue;
		father[fx]=fy;
		f[fy]=(f[fx]+E[i].z-g[fx])*(f[fy]+E[i].z-g[fy])%MOD;
		g[fy]=E[i].z;
	}
	int fa=find(1);
	printf("%lld",(f[fa]+h-g[fa])%MOD);
    return 0;
}