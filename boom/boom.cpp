#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 20

int n,book1[MAXN],book2[MAXN],book3[MAXN],finish1[MAXN],finish2[MAXN],finish3[MAXN];
int ans,a[MAXN],b[MAXN],c[MAXN];

void dfs3(int x,int ti)
{
	if(x==n+1)
	{
		int res=0;
		for(int i=1;i<=n;i++)
		{
			res=max(res,finish1[i]);
			res=max(res,finish2[i]);
			res=max(res,finish3[i]);
		}
		ans=min(ans,res);
		return;
	}
	for(int i=1;i<=n;i++)
	{
		if(!book3[i])
		{
			book3[i]=1;
			finish3[i]=max(ti,finish2[i])+c[i];
			dfs3(x+1,max(ti,finish2[i])+c[i]);
			book3[i]=0;
		}
	}
}

void dfs2(int x,int ti)
{
	if(x==n+1)
	{
		dfs3(1,0);
		return;
	}
	for(int i=1;i<=n;i++)
	{
		if(!book2[i])
		{
			book2[i]=1;
			finish2[i]=max(ti,finish1[i])+b[i];
			dfs2(x+1,max(ti,finish1[i])+b[i]);
			book2[i]=0;
		}
	}
}

void dfs1(int x,int ti)
{
	if(x==n+1) 
	{
		dfs2(1,0);
		return;
	}
	for(int i=1;i<=n;i++)
	{
		if(!book1[i])
		{
			book1[i]=1;
			finish1[i]=ti+a[i];
			dfs1(x+1,finish1[i]);
			book1[i]=0;
		}
	}
}

int main()
{
    //freopen("input","r",stdin);
    scanf("%d",&n);ans=1e9;
    for(int i=1;i<=n;i++)
    	scanf("%d %d %d",&a[i],&b[i],&c[i]);
    dfs1(1,0);
    cout<<ans;
    return 0;
}