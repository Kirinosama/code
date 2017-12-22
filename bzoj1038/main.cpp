#include<cmath>  
#include<cstdio>  
#include<cstring>  
#include<iostream>  
#include<algorithm>  
#define M 310  
using namespace std;  
struct point{  
    double x,y;  
    point(){}  
    point(double X,double Y)  
    {  
        x=X;  
        y=Y;  
    }  
}points[M];  
point operator - (const point &x,const point &y)  
{  
    return point(x.x-y.x,x.y-y.y);  
}  
double operator * (const point &x,const point &y)  
{  
    return x.x*y.y-y.x*x.y;  
}  
struct line{  
    point *p1,*p2;  
    double k,b;  
    void get_function()  
    {  
        point p=(*p2)-(*p1);  
        k=(double)p.y/p.x;  
        b=p1->y-k*p1->x;  
    }  
    double f(double x)  
    {  
        return k*x+b;  
    }  
}lines[M];  
int n;  
double ans,ansheight=1e11;  
double Rand()  
{  
    return rand()%1000/1000.0;  
}  
bool Judge(point p)  
{  
    int i;  
    for(i=2;i<=n;i++)  
    {  
        if( (points[i-1]-p)*(points[i]-p)<0 )  
            return false;  
    }  
    return true;  
}  
double f(double x)  
{  
    int i;  
    for(i=2;i<=n;i++)  
        if( x>=lines[i].p1->x && x<=lines[i].p2->x )  
            return lines[i].f(x);  
}  
double Divide(double x)  
{  
    double l=0,r=1e11;  
    double mid=(l+r)/2;  
    while(r-l>1e-7)  
    {  
        if( Judge( point(x,mid) ) )  
            r=mid;  
        else  
            l=mid;  
        mid=(l+r)/2;  
    }  
    mid-=f(x);  
    if(mid<ansheight)  
        ans=x,ansheight=mid;  
    return mid;  
}  
void SA(double T)  
{  
    int i;  
    double Now=ans;  
    for(;T>0.00001;T*=0.99)  
    {  
        double Neo=Now+T*(Rand()*2-1);  
        if( Neo<points[1].x || Neo>points[n].x )  
            continue;  
        double dE = Divide(Now) - Divide(Neo);  
        if( dE>0 || exp(dE/T)>Rand() )  
            Now=Neo;  
    }  
    for(i=1;i<=1000;i++)  
    {  
        double Neo=ans+T*(Rand()*2-1);  
        if( Neo<points[1].x || Neo>points[n].x )  
            continue;  
        Divide(Neo);  
    }  
}  
int main()  
{  
    srand(20001116);  
    int i;  
    cin>>n;  
    for(i=1;i<=n;i++)  
        scanf("%lf",&points[i].x);  
    for(i=1;i<=n;i++)  
        scanf("%lf",&points[i].y);  
    for(i=2;i<=n;i++)  
        lines[i].p1=&points[i-1],lines[i].p2=&points[i],lines[i].get_function();  
    ans=(points[n].x+points[1].x)/2.0;  
    SA( points[n].x-points[1].x );  
    printf("%.3lf\n",ansheight+1e-7);  
}  