#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

int n,x;

int main()
{
	freopen("input","r",stdin);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&x);
		if(x%2==1)
		{
			printf("First");
			return 0;
		}
	}
	printf("Second");
	return 0;
}