#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <vector>
#include <cmath>
using namespace std;

const double eps=1e-8;
const int INF=0x3f3f3f3f;
#define MAXN 100010

int father[MAXN],f[MAXN],a[MAXN],n;

int main()
{
	freopen("input","r",stdin);
	freopen("output","w",stdout);
	scanf("%d",&n);
	if(n==0)
	{
		printf("a");
		return 0;
	}
	f[0]=1;
	for(int i=1;i<=26;i++)
	{
		for(int j=n;j>=1;j--)
		{
			if(f[j]) continue;
			for(int k=2;k<=500;k++)
			{	
				int minus=(k*(k-1))/2;
				if(j-minus<0) break;
				if(f[j-minus])
				{
					f[j]=1;
					father[j]=k;
					break;
				}
			}
		}
		if(f[n]) break;
	}
	int cnt=0;
	while(n)
	{
		a[++cnt]=father[n];
		n-=(father[n]*(father[n]-1))/2;
	}
	for(int i=1;i<=cnt;i++)
	{
		for(int j=1;j<=a[i];j++)
			printf("%c",'a'+i-1);
	}
	return 0;
}
