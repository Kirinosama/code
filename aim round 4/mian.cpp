#include <cstdlib>
#include <cstdio>

int main()
{
	double a=1.0;
	for(int i=1;i<=1000;i++)
		a*=0.98;
	printf("%.100f",a);
	return 0;
}