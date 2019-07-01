#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<vector>
#include<stack> 
#define M 101000
using namespace std;
vector<int>map[11000];
stack<int>c;
int dfn[M],low[M],vis[M],inf=1,n,m,po,ans[M];
void dfs(int now)
{
	c.push(now);
	dfn[now]=inf;
	low[now]=inf;
	vis[now]=1;
	inf++;
	for (int i=0;i<int(map[now].size());i++)
	{
		if (!dfn[map[now][i]])
		{
			dfs(map[now][i]);
			low[now]=min(low[now],low[map[now][i]]);
		}
		else if (vis[map[now][i]])
		{
			low[now]=min(low[now],low[map[now][i]]);
		}
	}
	if (dfn[now]==low[now])
	{
		vis[now]=0;
		while (c.top()!=now)
		{
			vis[c.top()]=0;
			c.pop();
		}
		c.pop();
	}
}
int main()
{
	scanf("%d %d",&n,&m);
	for (int i=1;i<=m;i++)
	{
		int x,y;
		scanf("%d %d",&x,&y);
		map[x].push_back(y);
	}
	for (int i=1;i<=n;i++)
	{
		if (!dfn[i])
		{
			dfs(i);
		}
	}
	for (int i=1;i<=n;i++)
	{
		for (int j=0;j<int(map[i].size());j++)
		{
			if (low[map[i][j]]>=dfn[i])
			{
				for (int k=1;k<=po;k++)
				{
					if (ans[k]==i)
					{
						continue;
					}
				}
				ans[++po]=i;
			}
		}
	}
	sort(ans+1,ans+po+1);
	for (int i=1;i<=po;i++)
	{
		printf("%d\n",ans[i]);
	}
	return 0;
}
