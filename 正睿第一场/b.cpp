#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MOD=998244353;
typedef long long ll;

int n,m;
ll f[5010][5010];

ll dfs(int x,int y)
{
	ll res=0;
	if(f[x][y]) return f[x][y];
	if(!y)
	{
		if(x==1) return 1;
		else return 0;
	}
	if(x==1) return f[x][y]=1;
	for(int i=1;i<x;i++)
		res=(res+dfs(i,y-1)*dfs(x-i,y))%MOD;
	return f[x][y]=res%MOD;
}

int main()
{
//	freopen("input","r",stdin);
	scanf("%d %d",&m,&n);
	for(int i=1;i<=n;i++)
		cout<<dfs(i,m-1)<<endl;
	return 0;
}
