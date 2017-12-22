#include <cstdio>  
#include <cstring>  
#include <iostream>  
#include <algorithm>  
#define INF 0x3f3f3f3f  
using namespace std;  
struct Point{  
    int x,y,z,f;  
    friend istream& operator >> (istream& _,Point &p)  
    {  
        scanf("%d%d%d",&p.x,&p.y,&p.z);  
        p.f=-INF;  
        return _;  
    }  
    bool operator < (const Point &p) const  
    {  
        if(y!=p.y)  
            return y<p.y;  
        return x<p.x;  
    }  
    friend int Distance(const Point &p1,const Point &p2)  
    {  
        return (p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y);  
    }  
    void Update(const Point &p)  
    {  
        f=max(f,p.f-Distance(p,*this)+z);  
    }  
}points[200200];  
int n,m;  
Point *now[1010];  
int main()  
{  
    #ifndef ONLINE_JUDGE  
    freopen("1560.in","r",stdin);  
    #endif  
    int i,j;  
    cin>>n>>m;  
    for(i=1;i<=n;i++)  
        cin>>points[i];  
    sort(points+1,points+n+1);  
    points[1].f=points[1].z;  
    for(i=1;i<=n;i++)  
    {  
        for(j=1;j<=points[i].x;j++)  
            if(now[j])  
                points[i].Update(*now[j]);  
        now[j-1]=&points[i];  
    }  
    cout<<points[n].f<<endl;  
    return 0;  
}  