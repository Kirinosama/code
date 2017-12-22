#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

#define MAXN 1000010

char a[MAXN];x
int n,ne[MAXN];

void make()
{
	for(int i=1;i<n;i++)
	{
		int temp=ne[i];
		while(temp && a[temp+1]!=a[i+1]) temp=ne[temp];
		if(a[temp+1]==a[i+1]) ne[i+1]=temp+1;
	}
}

int main()
{
	freopen("input","r",stdin);
	scanf("%d\n",&n);
	for(int i=1;i<=n;i++) scanf("%c",&a[i]);
	make();
	cout<<n-ne[n];
	return 0;
}