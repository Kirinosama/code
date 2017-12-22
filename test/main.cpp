#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <set>
#include <iostream>
using namespace std;

int n,m,x;

set <int> a;

int main()
{
	freopen("input","r",stdin);
	scanf("%d %d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d",&x);
		a.insert(x);
	}
	printf("%d",a.lower_bound(n)==a.begin());
	return 0;
}