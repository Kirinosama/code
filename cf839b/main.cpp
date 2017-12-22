#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

int n,k,cnt,mid,a[10010];

int main()
{
	freopen("input","r",stdin);
	scanf("%d %d",&n,&k);
	mid=n;
	for(int i=1;i<=k;i++)
	{
		scanf("%d",&a[i]);
		if(a[i]>=4)
		{
			int tmp=min(mid,a[i]/4);
			mid-=tmp;
			a[i]-=tmp*4;
		}
	}
	int rem=mid+n*2;
	for(int i=1;i<=k;i++)
	{
		if(a[i]%2 && mid)
		{
			a[i]--;mid--;
		}
	}
	for(int i=1;i<=k;i++)
	{
		while(a[i]>=2 && mid>=2)
			a[i]-=2,mid-=2;
	}
	for(int i=1;i<=k;i++)
		cnt+=(a[i]+1)/2;
	if(cnt<=rem) printf("YES");
	else printf("NO");
	return 0;
}