#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

#define MAXN 1010

using namespace std;

int top=0;

struct Point
{
    double x,y;
    Point(){}
    Point(double _x,double _y):x(_x),y(_y){}
}points[MAXN];

Point operator-(Point a,Point b)
{
    return Point(a.x-b.x,a.y-b.y);
}

double cross(Point a,Point b)
{
    return a.x*b.y-a.y*b.x;
}

struct Line
{
    Point a,b;
    double k,c; 
    void get()
    {
        k=(a.y-b.y)/(a.x-b.x);
        c=a.y-k*a.x;
    }
}lines[MAXN],stack[MAXN];

int n;
double ans=1e6;

Point getIntersec(Line a,Line b) 
{
    Point t;
    t.x=(a.c-b.c)/(b.k-a.k);
    t.y=t.x*a.k+a.c;
    return t;
}

void Insert(Line t)
{
    while(top>=2)
    {
        if(getIntersec(stack[top-1],stack[top]).x>getIntersec(stack[top],t).x) top--;
        else break;
    }
    stack[++top]=t;
}

void halfPanelIntersec()
{
    for(int i=1;i<n;i++)
        Insert(lines[i]);
}

double calc1(double x)
{
    double maxh=0;
    for(int i=1;i<=top;i++)
        maxh=max(maxh,stack[i].k*x+stack[i].c);
    return maxh;
}

double calc2(double x) 
{
    for(int i=2;i<=n;i++)
    {
        if(points[i].x>=x)
            return points[i].y-(points[i].y-points[i-1].y)*(points[i].x-x)/(points[i].x-points[i-1].x);
    }
    return 0;
}

bool cmp(Line a,Line b)
{
    return a.k<b.k;
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%lf",&points[i].x);
    for(int i=1;i<=n;i++)
        scanf("%lf",&points[i].y);
    for(int i=1;i<n;i++)
        lines[i].a=points[i],lines[i].b=points[i+1],lines[i].get();
    sort(lines+1,lines+n,cmp);
    halfPanelIntersec();
    for(int i=1;i<=n;i++)
        ans=min(ans,calc1(points[i].x)-points[i].y);
    for(int i=1;i<top;i++)
    {
        Point tmp=getIntersec(stack[i],stack[i+1]);
        ans=min(ans,tmp.y-calc2(tmp.x));
    }
    printf("%.3lf\n",ans);
    return 0;
}