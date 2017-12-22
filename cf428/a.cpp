#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

#define MAXN 110

int cnt,give,k,n,a[MAXN];

int main()
{
	freopen("input","r",stdin);
	scanf("%d %d",&n,&k);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)
	{
		cnt+=a[i];
		give=min(cnt,8);
		cnt-=give;
		k-=min(give,k);
		if(k==0)
		{
			printf("%d",i);
			return 0;
		}
	}
	printf("-1");
	return 0;
}