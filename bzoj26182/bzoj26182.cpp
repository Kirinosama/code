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

struct node{
	double x,y;
	node(){}
	node(double X,double Y){x=X,y=Y;}
	node operator - (const node &a)const{
		return node(x-a.x,y-a.y);
	}
	double dis(const node &a)const{
		return sqrt((x-a.x)*(x-a.x)+(y-a.y)*(y-a.y));
	}
	double cross(const node &a)const{
		return x*a.y-y*a.x;
	}
}p[60],anss[50010];

struct edge{
	node a,b,c;
	edge(){}
	edge(node A,node B){a=A,b=B,c=B-A;}
}E[610],q[610];

int cnt;

inline int read(){
	int x=0,w=0;char ch;
	while(ch<'0' || ch>'9') w|=(ch=='-'),ch=getchar();
	while(ch>='0' && ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return w?-x:x;
}

bool onleft (edge a,edge b){
	double res=a.c.cross(b.c);
	return (res>0 || (res==0 && a.c.cross(b.a-a.a)>0));
}

bool cmp(const edge &a,const edge &b){
	if(a.c.y==0 && b.c.y==0) return a.c.x<b.c.x;
	if(a.c.y<=0 && b.c.y<=0) return onleft(a,b);
	else if(a.c.y>0 && b.c.y>0) return onleft(a,b);
	else return a.c.y<b.c.y;
}

node inter (edge a,edge b){
	if(a.a.x==a.b.x){
		double k=(b.b.y-b.a.y)/(b.b.x-b.a.x);
		double t=b.a.y-b.a.x*k;
		return node(a.a.x,k*a.a.x+t);
	}else if(b.a.x==b.b.x){
		double k=(a.b.y-a.a.y)/(a.b.x-a.a.x);
		double t=a.a.y-a.a.x*k;
		return node(b.a.x,k*b.a.x+t);
	}else{
		double k1=(a.b.y-a.a.y)/(a.b.x-a.a.x);
		double t1=a.a.y-a.a.x*k1;
		double k2=(b.b.y-b.a.y)/(b.b.x-b.a.x);
		double t2=b.a.y-b.a.x*k2;
		double x=(t2-t1)/(k1-k2),y=k1*x+t1;
		return node(x,y);
	}
}

bool onright(node a,edge e){
	return (a-e.a).cross(e.c)>=0;
}

void solve(){
	sort(E+1,E+cnt+1,cmp);
	int cnt1=0;
	for(int i=1;i<=cnt;i++){
		if(i==1 || E[i].c.cross(E[i-1].c)!=0) cnt1++;
		E[cnt1]=E[i];
	}cnt=cnt1;
	int head=1,tail=0;
	for(int i=1;i<=cnt;i++){
		while(head<tail && onright(inter(q[tail],q[tail-1]),E[i])) tail--;
		while(head<tail && onright(inter(q[head],q[head+1]),E[i])) head++;
		q[++tail]=E[i];
	}
	while(head<tail && onright(inter(q[tail],q[tail-1]),q[head])) tail--;
	int ans_cnt=0;q[tail+1]=q[head];
	for(int i=head;i<=tail;i++) anss[++ans_cnt]=inter(q[i],q[i+1]);
	anss[ans_cnt+1]=anss[1];
	double ans=0.0;
	for(int i=1;i<=ans_cnt;i++) ans+=anss[i].cross(anss[i+1])/2.0;
	printf("%.3lf",ans);
}

int main(){
    freopen("bzoj26182.in","r",stdin);
    int t=read();
    while(t--){
    	int n=read();
    	for(int i=1;i<=n;i++)scanf("%lf%lf",&p[i].x,&p[i].y);
    	p[n+1]=p[1];
 		for(int i=1;i<=n;i++)E[++cnt]=edge(p[i],p[i+1]);
    }
	solve();
    return 0;
}