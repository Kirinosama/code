#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

#define MAXN 2010
#define eps 1e-8

struct node{
	double x,y;
	node(double a=0,double b=0){x=a,y=b;}
	node operator - (const node &a)const{
		return node(x-a.x,y-a.y);
	}
	double operator * (const node &a)const{
		return x*a.y-y*a.x;
	}
}p[MAXN];

struct line{
	node a,b;
	double ang;
	line(){}
	line(node c,node d){
		a=c,b=d;
		ang=atan2((d-c).y,(d-c).x);
	}
}l[MAXN],q[MAXN];

bool cmp(const line &p,const line &q){
	if(fabs(p.ang-q.ang)<eps) return (q.b-q.a)*(p.b-q.a)>0;
	else return p.ang<q.ang;
}

node get(line p,line q){
	double c1=p.a*q.b+q.b*q.a+q.a*p.a;
	double c2=q.b*p.b+p.b*q.a+q.a*q.b;
	return node(p.a.x+(p.b.x-p.a.x)*c1/(c1+c2),(p.a.y+p.b.y-p.a.y)*c1/(c1+c2));
}

bool isonright(node q,line p){
	return (q-p.a)*(p.b-p.a)>=-eps;
}

int n,T,cnt;

void bpmj(){
	int head=1,tail=0;double ans=0;
	int cnt1=0;
	for(int i=1;i<=cnt;i++)if(!cnt1 || (l[i].ang-l[cnt1].ang>eps))
		l[++cnt1]=l[i];
	cnt=cnt1;
	for(int i=1;i<=cnt;i++){
		while(tail-head>1 && isonright(get(q[tail],q[tail-1]),l[i])) tail--;
		while(tail-head>1 && isonright(get(q[head],q[head+1]),l[i])) head++;
		q[++tail]=l[i];
	}
	while(tail-head>1 && isonright(get(q[tail],q[tail-1]),q[head])) tail--;
	while(tail-head>1 && isonright(get(q[head],q[head+1]),q[tail])) head++;
	q[tail+1]=q[head];
	for(int i=head;i<=tail;i++)p[i]=get(q[i],q[i+1]);
	for(int i=head;i<=tail;i++)printf("%.2f %.2f\n",p[i].x,p[i].y);
	p[tail+1]=p[head];
	for(int i=head;i<=tail;i++)ans+=p[i]*p[i+1];
	printf("%.2f",ans);
}

void solve(){
	cin>>n;
	for(int i=1;i<=n;i++)scanf("%lf%lf",&p[i].x,&p[i].y);
	p[n+1]=p[1];
	for(int i=1;i<=n;i++)l[++cnt]=line(p[i],p[i+1]);
}

int main(){
	freopen("p4196.in","r",stdin);
	cin>>T;
	while(T--)solve();
	sort(l+1,l+cnt+1,cmp);
	bpmj();
	return 0;
}
