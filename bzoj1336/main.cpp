#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <iostream>
using namespace std;

const double eps=1e-12;
#define MAXN 100010

struct node
{
	double x,y;
}p[MAXN],o;

int n;
double r,q[5][5];

double fabs(double x) {return x>=0 ? x : -x;}

double dis(node a,node b)
{
	return (double)sqrt(fabs(a.x-b.x)*fabs(a.x-b.x)+fabs(a.y-b.y)*fabs(a.y-b.y));
}

bool judge(node t)
{
	return dis(t,o)<r+eps;
}

void solve(node a, node b, node c) {  
    q[1][1]=2*(b.x-a.x),q[1][2]=2*(b.y-a.y),q[1][3]=(b.x*b.x+b.y*b.y-a.x*a.x-a.y*a.y);  
    q[2][1]=2*(c.x-a.x),q[2][2]=2*(c.y-a.y),q[2][3]=(c.x*c.x+c.y*c.y-a.x*a.x-a.y*a.y);  
    for(int i = 1; i <= 2; i++)  
    for(int j = 1; j <= 2; j++) if(i != j) {  
        double x = q[j][i]/q[i][i];  
        for(int k = 1; k <= 3; k++) q[j][k] -= x*q[i][k];  
    }  
	o.x=q[1][3]/q[1][1];o.y=q[2][3]/q[2][2];
}  

int main()
{
	freopen("input","r",stdin);
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%lf %lf",&p[i].x,&p[i].y);
	random_shuffle(p+1,p+1+n);
	o=p[1];r=0;
	for(int i=2;i<=n;i++)
	{
		if(judge(p[i])) continue;
		o.x=(p[i].x+p[1].x)/2,o.y=(p[i].y+p[1].y)/2;
		r=dis(o,p[1]);
		for(int j=2;j<i;j++)
		{
			if(judge(p[j])) continue;
			o.x=(p[j].x+p[i].x)/2;
			o.y=(p[j].y+p[i].y)/2;
			r=dis(p[j],o);
			for(int k=1;k<j;k++)
			{
				if(judge(p[k])) continue;
				solve(p[i],p[j],p[k]);
				r=dis(p[i],o);
			}
		}
	}
	printf("%.10f\n%.10f %.10f",r,o.x,o.y);
	return 0;
}