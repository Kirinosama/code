#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 400
#define MAXM 100010

int n,w[MAXN],sum,f[MAXM];

int main()
{
	freopen("input","r",stdin);
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&w[i]),sum+=w[i];
	sort(w+1,w+1+n,greater<int>());
	f[0]=1;
	for(int i=1;i<=n;i++)
	{
		for(int j=sum;j>=0;j--)
			if(j-w[i]<=sum/2 && j-w[i]>=0 && f[j-w[i]]==1) f[j]=1;
	}
	for(int i=sum;i>=0;i--) 
	{
		if(f[i])
		{
			printf("%d",i);
			break;
		}
	}
	return 0;
}
