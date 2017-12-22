#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

#define MAXN 1010
#define ii pair<int,int>

vector <ii> e[MAXN];
int n,flag;

void dfs(int x,int k)
{
	if(x==n){
		flag=1;
		printf("%d",k);
	}
	if(flag) return; 
	for(int i=0;i<e[x].size();i++)
	{
		int to=e[x][i].first;
		if(e[x][i].second==1) dfs(to,k^1);
		else dfs(to,k);
	}
}

int main()
{
	freopen("input","r",stdin);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		static int x,y,z;
		scanf("%d %d %d",&x,&y,&z);
		e[x].push_back(ii(y,z));
	}
	dfs(1,0);
}