#include <bits/stdc++.h>
using namespace std;

#define MAXN 2010
const double INF=9999999.0;

int n,m,v,e,a[MAXN],b[MAXN];
int dis[310][310];
double k[MAXN],ans,dp[MAXN][MAXN][2];

int main(){
	freopen("input","r",stdin);
	cin>>n>>m>>v>>e;
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)scanf("%d",&b[i]);
	for(int i=1;i<=n;i++)scanf("%lf",&k[i]);
	memset(dis,0x3f,sizeof(dis));
	for(int i=1;i<=e;i++){
		static int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		dis[x][y]=dis[y][x]=min(dis[x][y],z);
	}
	for(int k=1;k<=v;k++)
		for(int i=1;i<=v;i++)
			for(int j=1;j<=v;j++)
				dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
	for(int i=1;i<=v;i++)dis[i][i]=0;
	for(int i=0;i<=m;i++)dp[1][i][0]=dp[1][i][1]=INF;
	dp[1][1][1]=dp[1][0][0]=0;
	for(int i=2;i<=n;i++){
		for(int j=0;j<=m;j++){
			dp[i][j][0]=dp[i][j][1]=INF;
			if(dp[i-1][j][0]!=INF)dp[i][j][0]=min(dp[i][j][0],dp[i-1][j][0]+dis[a[i]][a[i-1]]);
			if(dp[i-1][j][1]!=INF)dp[i][j][0]=min(dp[i][j][0],dp[i-1][j][1]+dis[a[i]][b[i-1]]*k[i-1]+dis[a[i]][a[i-1]]*(1.0-k[i-1]));
			if(j==0)continue;
			if(dp[i-1][j-1][0]!=INF)dp[i][j][1]=min(dp[i][j][1],dp[i-1][j-1][0]+dis[b[i]][a[i-1]]*k[i]+dis[a[i]][a[i-1]]*(1.0-k[i]));
			if(dp[i-1][j-1][1]!=INF)dp[i][j][1]=min(dp[i][j][1],dp[i-1][j-1][1]+dis[b[i]][b[i-1]]*k[i]*k[i-1]+
														dis[a[i]][b[i-1]]*(1.0-k[i])*k[i-1]+
														dis[b[i]][a[i-1]]*k[i]*(1.0-k[i-1])+
														dis[a[i]][a[i-1]]*(1.0-k[i])*(1.0-k[i-1]));
		}
	}
	ans=INF;
	for(int i=0;i<=m;i++){
		ans=min(ans,dp[n][i][0]);
		ans=min(ans,dp[n][i][1]);
	}
	printf("%.2lf",ans);
	return 0;
}
