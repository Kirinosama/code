#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 200010

struct node
{
	int pos,val;
}p[MAXN];

int n,a[MAXN],b[MAXN],ans[MAXN];

bool cmp(node a,node b)
{
	return a.val<b.val;
}

int main()
{
	freopen("input","r",stdin);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		a[i]=-a[i];
	}
	for(int i=1;i<=n;i++) 
	{
		scanf("%d",&b[i]);
		p[i].pos=i;p[i].val=b[i];
	}
	sort(p+1,p+1+n,cmp);
	sort(a+1,a+1+n);
	for(int i=1;i<=n;i++)
	{
		ans[p[i].pos]=-a[i];
	}
	for(int i=1;i<=n;i++) printf("%d ",ans[i]);
	return 0;
}