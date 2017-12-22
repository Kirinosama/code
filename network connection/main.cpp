#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 2010
#define MAXM 100010

const long long INF=0x7ffffffffff;
long long a[MAXM],b[MAXN],ans;
long long min1[MAXM],dp[MAXM];
int n,m,near[MAXN];

long long abs1(long long x)
{
	if(x<0)
		return -x;
	else
		return x;
}

int main()
{
	freopen("input","r",stdin);
	scanf("%d %d",&m,&n);
	for(int i=1;i<=m;i++)
		cin>>a[i];
	for(int i=1;i<=n;i++)
		cin>>b[i];
	sort(a+1,a+m+1);sort(b+1,b+1+n);
	for(int i=1;i<=m;i++)
		dp[i]=abs1(b[1]-a[i]);
	near[0]=1;
	for(int i=1;i<=n;i++)
	{
		int pos=near[i-1];
		while(abs1(a[pos+1]-b[i])<=abs1(a[pos]-b[i]) && pos+1<=m)
			pos++;
		near[i]=pos;
	}
	for(int i=2;i<=n;i++)
	{
		int r=min(m-n+i,near[i]+n+10);
		int l=max(i,near[i]-n-10);
		min1[l-1]=dp[l-1];
		for(int j=l;j<=r-1;j++)
			min1[j]=min(dp[j],min1[j-1]);
		for(int j=r;j>=l;j--)
			dp[j]=min1[j-1]+abs1(b[i]-a[j]);
	}
	ans=INF;
	for(int i=n;i<=m;i++)
		ans=min(ans,dp[i]);
	cout<<ans;
//	for(int i=1;i<=n;i++)
//		printf("%d ",near[i]);
	return 0;
}