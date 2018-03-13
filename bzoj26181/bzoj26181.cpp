#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int n,all,cnt;

struct point{
	double x,y;
	point(){}
	point(double x_,double y_){x=x_,y=y_;}
	double dis (const point &a)const{
		return sqrt((x-a.x)*(x-a.x)+(y-a.y)*(y-a.y));
	}
	double cross (const point &a)const{
		return x*a.y-y*a.x;
	}
	point operator - (const point &a)const{
		return point(x-a.x,y-a.y);
	}
	void in(){scanf("%lf%lf",&x,&y);}
}p[60],anss[50010];

struct edge{
	point a,b,v;
	edge(){}
	edge(point x,point y){a=x,b=y,v=y-x;}
}E[510],q[510];

bool cmp (const edge &a,const edge &b){
	if(a.v.y==0 && b.v.y==0) return a.v.x<b.v.x;
	if((a.v.y<=0)!=(b.v.y<=0)) return a.v.y<b.v.y;
	if(a.v.cross(b.v)==0) return (a.b-a.a).cross(b.a-a.a)>0;
	else return a.v.cross(b.v)>0;
}

point inter(edge e1,edge e2){
	double k1=(e1.b.y-e1.a.y)/(e1.b.x-e1.a.x),b1=e1.a.y-k1*e1.a.x;
	double k2=(e2.b.y-e2.a.y)/(e2.b.x-e2.a.x),b2=e2.a.y-k2*e2.a.x;
	double x=(b2-b1)/(k1-k2);
	return point(x,k1*x+b1);
}

bool isonright (point a,edge e){
	return e.v.cross(a-e.a)<=0;
}

bool par(edge a,edge b){
	return a.v.cross(b.v)==0;
}

void solve(){
	int head=1,tail=0,cnt1=0;
	for(int i=1;i<=cnt;i++){
		if(i==1 || !par(E[i],E[i-1])) cnt1++;
		E[cnt1]=E[i];
	}cnt=cnt1;
	for(int i=1;i<=cnt;i++){
		while(head<tail && isonright(inter(q[tail],q[tail-1]),E[i])) tail--;
		while(head<tail && isonright(inter(q[head],q[head+1]),E[i])) head++;
		q[++tail]=E[i];
	}
	while(head<tail && isonright(inter(q[tail],q[tail-1]),q[head])) tail--;
	q[tail+1]=q[head];int sum=0;
	if(tail-head+1<=2){
		printf("0.000");
		return;
	}
	for(int i=head;i<=tail;i++)
		anss[++sum]=inter(q[i],q[i+1]);
	anss[0]=anss[sum];anss[sum+1]=anss[1];
	double ans=0;
	for(int i=1;i<=sum;i++) ans+=anss[i].cross(anss[i+1]);
	printf("%.3lf",ans/2.0);
}

int main(){
    freopen("bzoj26181.in","r",stdin);
    scanf("%d",&all);
    while(all--){
    	scanf("%d",&n);
    	for(int i=1;i<=n;i++)p[i].in();
    	p[n+1]=p[1];
    	for(int i=1;i<=n;i++)E[++cnt]=edge(p[i],p[i+1]);
    }
	sort(E+1,E+cnt+1,cmp);
	solve();
    return 0;
}