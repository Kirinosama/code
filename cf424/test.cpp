#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <iostream>
using namespace std;

int main()
{
	freopen("input","w",stdout);
	srand(time(0));
	int n=rand()%100+1;
	int m=rand()%100+1;
	int k=rand()%150+1;
	printf("%d %d\n",n,m);
	for(int i=1;i<=m;i++)
	{
		int x=rand()%100+1;
		printf("%d %d\n",x,(x+k-1)/k);
	}
	printf("%d\n%d",k,(n+k-1)/k);

	return 0;
}