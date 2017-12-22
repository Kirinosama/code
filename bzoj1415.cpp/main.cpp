#include<iostream>
#include<cstdio>
#include<queue>
#include<cstring>
#include<vector>
#define MAXN 1010
using namespace std;
double dp[MAXN][MAXN];
bool calc[MAXN][MAXN],vis[MAXN];
int dist[MAXN][MAXN],to[MAXN][MAXN];
vector<int> g[MAXN];queue<int> q;
int bfs(int s)
{
	memset(vis,false,sizeof(vis));
	while(!q.empty()) q.pop();
	vis[s]=true;to[s][s]=s;
	dist[s][s]=0;q.push(s);
	while(!q.empty())
	{
		int x=q.front();q.pop();
		for(int i=g[x].size()-1;i>=0;i--)
			if(!vis[g[x][i]])
			{
				int t=g[x][i];vis[t]=true;
				dist[s][t]=dist[s][x]+1;
				if(dist[s][t]<=1) to[s][t]=t;
				else to[s][t]=to[s][x];
				q.push(t);
			}
			else{
				int t=g[x][i];
				if(dist[s][t]<=1) continue;
				if(dist[s][t]!=dist[s][x]+1) continue;
				to[s][t]=min(to[s][t],to[s][x]);
			}
	}
	return 0;
}
double getdp(int x,int y)
{
	if(calc[x][y]) return dp[x][y];
	calc[x][y]=true;
	if(dist[x][y]==0) return dp[x][y]=0.0;
	if(dist[x][y]<=2) return dp[x][y]=1.0;
	dp[x][y]=getdp(to[to[x][y]][y],y);
	for(int i=g[y].size()-1;i>=0;i--)
		dp[x][y]+=getdp(to[to[x][y]][y],g[y][i]);
	return dp[x][y]=dp[x][y]/(1.0+g[y].size())+1.0;
}
int main()
{
	int n,m,s,t;scanf("%d%d%d%d",&n,&m,&s,&t);
	for(int i=1;i<=m;i++)
	{
		int u,v;scanf("%d%d",&u,&v);
		g[u].push_back(v);g[v].push_back(u);
	}
	for(int i=1;i<=n;i++) bfs(i);
	printf("%.3f\n",getdp(s,t));
	return 0;
}
