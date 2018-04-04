#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

#define MAXN 10010

struct node{
	double x,y;
	node(double a=0,double b=0){x=a,y=b;}
	node operator - (const node &a)const{
		return node(x-a.x,y-a.y);
	}
	double operator * (const node &a)const{
		return x*a.y-y*a.x;
	}
	double dis(const node &a)const {
		return sqrt((x-a.x)*(x-a.x)+(y-a.y)*(y-a.y));
	}
}p[MAXN],q[MAXN];

int n;

bool cmp(const node &a,const node &b){
	if(a.y==b.y)return a.x<b.x;
	else return a.y<b.y;
}

bool cmp1(const node &a,const node &b){
	double c=(a-p[1])*(b-p[1]);
	if(c==0) return a.dis(p[1])<b.dis(p[1]);
	return c>0;
}

void solve(){
	int head=1,tail=0;
	double ans=0;
	for(int i=1;i<=n;i++){
		while(tail-head>1 && (p[i]-q[tail-1])*(q[tail]-q[tail-1])>=0) tail--;
		q[++tail]=p[i];
	}
	q[tail+1]=p[1];
	for(int i=1;i<=tail;i++)ans+=q[i].dis(q[i+1]);
	printf("%.2f",ans);
}

int main(){
	freopen("p2742.in","r",stdin);
	cin>>n;
	for(int i=1;i<=n;i++)scanf("%lf%lf",&p[i].x,&p[i].y);
	for(int i=2;i<=n;i++)if(cmp(p[i],p[1]))
		swap(p[i],p[1]);
	sort(p+2,p+n+1,cmp1);
	solve();
	return 0;
}
