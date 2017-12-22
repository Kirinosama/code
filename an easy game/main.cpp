#include <cstdlib>
#include <cstdio>
#include <iostream>
using namespace std;

#define MAXN 110

int a[MAXN],b[MAXN];
int n,m,k;
int dif;

int main()
{
	cin>>n>>m>>k;
	getchar();
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	getchar();
	for(int i=1;i<=n;i++)
		scanf("%d",&b[i]);
	for(int i=1;i<=n;i++)
	{
		if(a[i]!=b[i])
			dif++;	
	}
	return 0;	
}