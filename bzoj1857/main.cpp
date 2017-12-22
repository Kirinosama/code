#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <cmath>
using namespace std;

#define P pair<double,double>
const double eps=1e-8;

struct node
{
	double x,y;
}a,b,c,d;

double p,q,r,lx,ly,rx,ry;

double dis(P x,P y)
{
	return (double)sqrt((x.first-y.first)*(x.first-y.first)+(x.second-y.second)*(x.second-y.second));
}

double cal1(double pos1x,double pos1y,double pos2x,double pos2y)
{
	P A=make_pair(a.x,a.y);
	P B=make_pair(pos1x,pos1y);
	P C=make_pair(pos2x,pos2y);
	P D=make_pair(d.x,d.y);
	return dis(A,B)/p + dis(B,C)/r + dis(C,D)/q;
}

double cal(double posx,double posy)
{
	double Lx=c.x,Ly=c.y,Rx=d.x,Ry=d.y;
	while(fabs(Lx-Rx)>eps || fabs(Ly-Ry)>eps)
	{
		double mid1x=Lx+(Rx-Lx)/3;
		double mid2x=Rx-(Rx-Lx)/3;
		double mid1y=Ly+(Ry-Ly)/3;
		double mid2y=Ry-(Ry-Ly)/3;
		double f1=cal1(posx,posy,mid1x,mid1y);
		double f2=cal1(posx,posy,mid2x,mid2y);
		if(f1<f2) Rx=mid2x,Ry=mid2y;
		else Lx=mid1x,Ly=mid1y;
	}
	return cal1(posx,posy,Lx,Ly);
}

int main()
{
	freopen("input","r",stdin);
	scanf("%lf %lf %lf %lf",&a.x,&a.y,&b.x,&b.y);
	scanf("%lf %lf %lf %lf",&c.x,&c.y,&d.x,&d.y);
	scanf("%lf %lf %lf",&p,&q,&r);
	lx=a.x;rx=b.x;ly=a.y;ry=b.y;
	while(fabs(rx-lx)>eps || fabs(ry-ly)>eps)
	{
		double mid1x=lx+(rx-lx)/3;
		double mid2x=rx-(rx-lx)/3;
		double mid1y=ly+(ry-ly)/3;
		double mid2y=ry-(ry-ly)/3;
		double f1=cal(mid1x,mid1y);
		double f2=cal(mid2x,mid2y);
		if(f1<f2) rx=mid2x,ry=mid2y;
		else lx=mid1x,ly=mid1y;
	}
	printf("%.2f",cal(lx,ly));
	return 0;
}