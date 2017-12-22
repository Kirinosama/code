#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

int t,cnt[110],n;

void add(int x,int k)
{
	for(int i=x;i;i-=(i&-i))
		cnt[i]+=k;
}

int make(int l,int r)
{
	int res=0;
	add(l-1,-1);
	add(r,1);
	for(int i=1;i<=n;i++)
		if(cnt[i]!=0)
			res++;
	return res;
}

void solve()
{
	int res=0;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		for(int j=i;j<=n;j++)
		{
			memset(cnt,0,sizeof(cnt));
			res+=make(i,j);
		}
	printf("%d\n",res);
}

int main()
{
	freopen("input","r",stdin);
	scanf("%d",&t);
	while(t--) solve();
	return 0;
}