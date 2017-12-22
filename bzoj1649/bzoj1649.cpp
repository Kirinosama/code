#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 1010
#define MAXM 10010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int last[MAXN],ne[MAXM],edge_cnt;
int n,m,b,ans,dp[MAXN][MAXN];

struct edge{
	int x,y,f,c;
}E[MAXM];

void add_edge(int x,int y,int f,int c){
	E[++edge_cnt]=(edge){x,y,f,c};
	ne[edge_cnt]=last[x];
	last[x]=edge_cnt;
}

int main(){
    freopen("bzoj1649.in","r",stdin);
    scanf("%d %d %d",&n,&m,&b);
    for(int i=1;i<=m;i++){
    	int x,y,f,c;
    	scanf("%d %d %d %d",&x,&y,&f,&c);
    	add_edge(y+x,x,f,c);
    }
    memset(dp,0xef,sizeof(dp));
    dp[0][0]=0;
    for(int i=1;i<=n;i++)
    	for(int j=last[i];j;j=ne[j]){
    		int y=E[j].y;
    		for(int k=0;k<=b;k++){
    			if(k-E[j].c<0) continue;
    			dp[i][k]=max(dp[i][k],dp[y][k-E[j].c]+E[j].f);
    		}
    	}
    ans=-1;
    for(int i=0;i<=b;i++)
    	ans=max(ans,dp[n][i]);
    printf("%d",ans);
    return 0;
}