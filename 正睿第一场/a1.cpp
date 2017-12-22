#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <iostream>
#include <cstring>
using namespace std;

int main()
{
	freopen("input","w",stdout);
	srand(time(0));
	int n=rand()%15+1;
	printf("%d\n",n);
	for(int i=1;i<=2*n;i++)
	{
		int a=rand()%9+1;
		int b=rand()%9999+1;
		double x=a+b*0.0001;
		printf("%.4f ",x);
	}
	return 0;
}