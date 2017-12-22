#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

const double eps=1e-8;
double r,d;
int n,ans;

double dis(double x,double y)
{
	return (double)sqrt(x*x+y*y);
}

void solve()
{
	double x,y,r1;
	scanf("%lf %lf %lf",&x,&y,&r1);
	if(dis(x,y)-r1>r-d-eps)
		if(dis(x,y)+r1<r+eps)
			ans++;
}

int main()
{
	freopen("input","r",stdin);
	scanf("%lf %lf %d",&r,&d,&n);
	for(int i=1;i<=n;i++)
		solve();
	cout<<ans;
	return 0;
}