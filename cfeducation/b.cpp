#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 210

int ans,a[MAXN],w[MAXN],n;

void check(int pos1,int pos2)
{
	int cnt=0;
	int res=0;
	for(int i=1;i<=2*n;i++)
		if(i!=pos1 && i!=pos2)
			a[++cnt]=w[i];
	sort(a+1,a+1+cnt);
	for(int i=1;i<=cnt;i+=2)
		res+=a[i+1]-a[i];
	ans=min(ans,res);
}

int main()
{
	freopen("input","r",stdin);
	scanf("%d",&n);
	ans=1e9;
	for(int i=1;i<=2*n;i++) scanf("%d",&w[i]);
	for(int i=1;i<=2*n;i++)
		for(int j=i+1;j<=2*n;j++)
			check(i,j);
		cout<<ans;
	return 0;
}