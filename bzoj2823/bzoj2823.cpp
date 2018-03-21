#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

#define eps 1e-6
#define MAXN 500010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

struct point{
	double x,y;
	point(){}
	point(double X,double Y){x=X,y=Y;}
	double dis(const point &a)const{
		return sqrt((x-a.x)*(x-a.x)+(y-a.y)*(y-a.y));
	}
}p[MAXN];

struct circle{
	point x;
	double r;
	circle(point X,double R){x=X,r=R;}
	circle(){}
	bool operator ^(const point &a)const{
		return x.dis(a)>r+eps;
	}
}c;

int n;

circle get_center(const point &a,const point &b,const point &c){
	point ret;
	double a1=b.x-a.x,b1=b.y-a.y,c1=(a1*a1+b1*b1)/2;
    double a2=c.x-a.x,b2=c.y-a.y,c2=(a2*a2+b2*b2)/2;
    double d=a1*b2-a2*b1;
    ret.x=a.x+(c1*b2-c2*b1)/d;
    ret.y=a.y+(a1*c2-a2*c1)/d;
    return circle(ret,ret.dis(a));
}

int main(){
    freopen("bzoj2823.in","r",stdin);
    cin>>n;
    for(int i=1;i<=n;i++)
    	scanf("%lf %lf",&p[i].x,&p[i].y);
    circle c(p[1],0);
    for(int i=2;i<=n;i++)if(c^p[i]){
    	c=circle(p[i],0);
    	for(int j=1;j<i;j++)if(c^p[j]){
    		c=circle(point((p[i].x+p[j].x)/2,(p[i].y+p[j].y)/2),p[i].dis(p[j])/2);
    		for(int k=1;k<j;k++)if(c^p[k])
    			c=get_center(p[i],p[j],p[k]);
    	}
    }
    printf("%.2f %.2f %.2f",c.x.x,c.x.y,c.r);
    return 0;
}