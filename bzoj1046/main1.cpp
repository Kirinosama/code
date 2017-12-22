#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 10010
#define MAXM 100010

int s[MAXN],maxx;
int n,m,dp[MAXN];

void solve()
{
	int k;
	int last=0;
	scanf("%d",&k);
	if(k>maxx) printf("Impossible\n");
	else 
	{
		for(int i=1;i<=n;i++)
			if(dp[i]>=k && s[i]>last)
			{
				printf("%d",s[i]);
				if(k!=1) printf(" ");
				last=s[i];
				k--;
				if(!k) break;
			}
		printf("\n");
	}
}

void premake()
{
	for(int i=1;i<=n;i++)
		dp[i]=1;
	for(int i=n-1;i>=1;i--)
	{
		for(int j=i+1;j<=n;j++)
			if(s[j]>s[i])
				dp[i]=max(dp[i],dp[j]+1);
		maxx=max(maxx,dp[i]);
	}
}

int main()
{
	freopen("input","r",stdin);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&s[i]);
	premake();
	scanf("%d",&m);
	while(m--)
		solve();
	return 0;
}