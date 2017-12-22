#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

#define MAXN 110

int ans,cnt,vis[MAXN],n,m;
vector <int> e1[MAXN];
vector <int> e2[MAXN];

void dfs1(int x)
{
	for(int i=0;i<e1[x].size();i++)
	{
		int v=e1[x][i];
		if(!vis[v])
		{
			vis[v]=1;
			cnt++;
			dfs1(v);
		}
	}
}

void dfs2(int x)
{
	for(int i=0;i<e2[x].size();i++)
	{
		int v=e2[x][i];
		if(!vis[v])
		{
			vis[v]=1;
			cnt++;
			dfs2(v);
		}
	}
}

void solve(int x)
{
	memset(vis,0,sizeof(vis));
	cnt=0;
	dfs1(x);dfs2(x);
	if(cnt==n-1) ans++;
}

int main()
{
	freopen("input","r",stdin);
	scanf("%d %d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		static int x,y;
		scanf("%d %d",&x,&y);
		e1[x].push_back(y);
		e2[y].push_back(x);
	}
	for(int i=1;i<=n;i++) solve(i);
	cout<<ans;
	return 0;
}