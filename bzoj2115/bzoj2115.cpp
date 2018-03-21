#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

//	注意无向图找环有重边 dfs记录来的边 不走同一条边
//	线性基顺着求

#define MAXN 300010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

const ll Log=63;

bool vis[MAXN];
ll d[MAXN],a[MAXN],M[MAXN];
int last[MAXN],ne[MAXN],edge_cnt;
int cnt,n,m;

struct edge{
	int x,y;ll z;
}E[MAXN];

void add_edge(int x,int y,ll z){
	E[++edge_cnt]=(edge){x,y,z};
	ne[edge_cnt]=last[x];
	last[x]=edge_cnt;
	E[++edge_cnt]=(edge){y,x,z};
	ne[edge_cnt]=last[y];
	last[y]=edge_cnt;
}

void dfs(int x,int f){
	vis[x]=true;
	for(int i=last[x];i;i=ne[i])if((i^1)!=f){
		int y=E[i].y;
		if(!vis[y]){
			d[y]=d[x]^E[i].z;
			dfs(y,i);
		}else a[++cnt]=d[x]^d[y]^E[i].z;
	}
}

void make_linear_basis(ll bit_mask){
	for(int i=1;i<=Log;i++)if(bit_mask&(1LL<<(Log-i))){
		if(M[i]){
			bit_mask^=M[i];
		}else{
			M[i]=bit_mask;
			for(int j=i+1;j<=Log;j++)if(M[i]&(1LL<<(Log-j)))M[i]^=M[j];
			for(int j=i-1;j>=1;j--)if(M[j]&(1LL<<(Log-i)))M[j]^=M[i];
			break;
		}
	}
}

int main(){
    freopen("bzoj2115.in","r",stdin);
   	scanf("%d%d",&n,&m);edge_cnt=1;
    for(int i=1;i<=m;i++){
    	static int x,y;
    	static ll k;
    	scanf("%d%d%lld",&x,&y,&k);
    	add_edge(x,y,k);
    }
    dfs(1,-1);
    for(int i=1;i<=cnt;i++)
	    make_linear_basis(a[i]);
	ll ans=d[n];
	for(int i=1;i<=Log;i++)
		if((ans^M[i])>ans)
			ans^=M[i];	
	printf("%lld\n",ans);
    return 0;
}