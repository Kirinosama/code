#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 100010

double s1[MAXN],s2[MAXN],sum1[MAXN],sum2[MAXN];
double ans;
int n;

void pre_make()
{
	for(int i=1;i<=n;i++)	scanf("%lf",&s1[i]);
	sort(s1+1,s1+1+n);
	for(int i=1;i<=n;i++)
		sum1[i]=sum1[i-1]+s1[n-i+1];
	for(int i=1;i<=n;i++)	scanf("%lf",&s2[i]);
	sort(s2+1,s2+1+n);
	for(int i=1;i<=n;i++)	
		sum2[i]=sum2[i-1]+s2[n-i+1];
}

void solve(int cur)
{
	int l=max(cur-n,0),r=min(n,cur);
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(sum1[mid]<=sum2[cur-mid])
		{
			ans=max(ans,sum1[mid]-cur);
			l=mid+1;
		}
		else r=mid-1;
	}
	l=max(cur-n,0);r=min(n,cur);
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(sum2[mid]<=sum1[cur-mid])
		{
			ans=max(ans,sum2[mid]-cur);
			l=mid+1;
		}
		else r=mid-1;
	}
}

int main()
{
	//freopen("input","r",stdin);
	scanf("%d",&n);
	pre_make();
	for(int i=1;i<=2*n;i++)
		solve(i);
	printf("%.4f",ans);
	return 0;
}
