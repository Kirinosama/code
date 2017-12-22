#include <cstdlib>
#include <cstdio>
#include <algorithm>
using namespace std;

#define MAXN 110

int ans;
int max1,n;
int a[MAXN];

int main()
{
	//freopen("input","r",stdin);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		max1=max(max1,a[i]);
	}
	for(int i=1;i<=n;i++)
		ans+=max1-a[i];
	printf("%d",ans);
	return 0;
}