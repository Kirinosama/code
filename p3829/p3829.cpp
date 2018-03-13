#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

#define eps 1e-8
#define MAXN 50010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int n,cnt;
double a,b,r;

struct node{
	double x,y;
	node(){}
	node(double x_,double y_){x=x_,y=y_;}
	node operator - (const node &a)const{
		return node(x-a.x,y-a.y);
	}
	node operator + (const node &a)const{
		return node(x+a.x,y+a.y);
	}
	double dis (const node &a)const{
		return sqrt(fabs(x-a.x)*fabs(x-a.x)+fabs(y-a.y)*fabs(y-a.y));
	}
	double cross (const node &a)const{
		return x*a.y-y*a.x;
	}
}p[MAXN],q[MAXN];

struct complex{
	double real,imag;
	complex(){}
	complex(double x_,double y_){real=x_,imag=y_;}
	node operator * (const complex &a)const{
		return node(real*a.real-imag*a.imag,real*a.imag+imag*a.real);
	}
};

bool cmp(const node &a,const node &b){
	return (a-p[1]).cross(b-p[1])>0;
}

void solve(double x,double y,double z){
	complex t(cos(z),sin(z));
	p[++cnt]=complex(-b/2.0+r,a/2.0-r)*t+node(x,y);
	p[++cnt]=complex(b/2.0-r,a/2.0-r)*t+node(x,y);
	p[++cnt]=complex(-b/2.0+r,-a/2.0+r)*t+node(x,y);
	p[++cnt]=complex(b/2.0-r,-a/2.0+r)*t+node(x,y);
}

void make(){
	double ans=0;
	for(int i=1;i<=cnt;i++)if(p[i].y<p[1].y)
		swap(p[1],p[i]);
	sort(p+1,p+cnt+1,cmp);
	int head=1,tail=0;
	for(int i=1;i<=cnt;i++){
		while(head<tail && (p[i]-q[tail-1]).cross(q[tail]-q[tail-1])>=-eps) tail--;
		q[++tail]=p[i];
	}
	q[tail+1]=q[head];
	for(int i=head;i<=tail;i++) ans+=q[i].dis(q[i+1]);
	ans+=2.0*r*M_PI;
	printf("%.2f",ans);
}

int main(){
    freopen("p3829.in","r",stdin);
    cin>>n>>a>>b>>r;
    for(int i=1;i<=n;i++){
    	double x,y,z;
    	scanf("%lf%lf%lf",&x,&y,&z);
    	solve(x,y,z);
    }
   // for(int i=1;i<=cnt;i++) printf("%lf %lf\n",p[i].x,p[i].y);
    make();
    return 0;
}