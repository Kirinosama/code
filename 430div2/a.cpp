#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const double eps=1e-8;
double l,r,x,y,k;

int main()
{
	freopen("input","r",stdin);
	scanf("%lf %lf %lf %lf %lf",&l,&r,&x,&y,&k);
	double lx=k*x;
	double ly=k*y;
	if(lx>r+eps || ly<l-eps)
		printf("NO");
	else 
		printf("YES");
	return 0;
}