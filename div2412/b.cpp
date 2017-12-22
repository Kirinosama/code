#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <set>
#include <queue>
#include <cmath>
using namespace std;

long long ax,bx,cx,ay,by,cy;
const double eps=1e-8;

bool judge()
{
	double Ax=(double)ax; double Ay=(double)ay;
	double Bx=(double)bx; double By=(double)by;
	double Cx=(double)cx; double Cy=(double)cy;
	if(Ax==Bx)
	{
		if(Bx==Cx) return true;
		return false;
	}
	else
	{
		double k1=(By-Ay)/(Bx-Ax);
		double b1=By-k1*Bx;
		if(fabs(k1*Cx+b1-Cy)<eps) return true;
		return false;
	}
}

int main()
{
	freopen("input","r",stdin);
	cin>>ax>>ay>>bx>>by>>cx>>cy;
	if(judge()) printf("No");
	else if((ax-bx)*(ax-bx)+(ay-by)*(ay-by)==(bx-cx)*(bx-cx)+(by-cy)*(by-cy)) printf("Yes");
	else printf("No");
	return 0;
}