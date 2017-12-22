#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <algorithm>
using namespace std;

int n,x,cnt[200],exist,ans;
int a[200];

int main()
{
	freopen("input","r",stdin);
	scanf("%d %d",&n,&x);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		cnt[a[i]]++;
		if(a[i]==x) exist++;
	}
	if(exist) ans++;
	for(int i=0;i<x;i++)
	{
		if(!cnt[i]) ans++;
	}
	cout<<ans;
	return 0;
}