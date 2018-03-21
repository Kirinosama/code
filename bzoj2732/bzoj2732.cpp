#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

#define eps 1e-8
#define MAXN 100010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int n,ans;
double x,y,z;

struct point{
	double x,y;
	point operator -(const point &a)const{
		return (point){x-a.x,y-a.y};
	}
	double operator *(const point &a)const{
		return x*a.y-y*a.x;
	}
}p[MAXN];

struct seg{
	point a,b;
	int id;
	double slope;
	void make(double ax,double ay,double bx,double by){
		a.x=ax,b.x=bx,a.y=ay,b.y=by;
		slope=atan2(b.y-a.y,b.x-a.x);
	}
}l[2*MAXN],s[2*MAXN],Q[2*MAXN];

int comp(double x,double y){
	if(fabs(x-y)<eps) return 0;
	return x<y?-1:1;
}

bool cmp(const seg &a,const seg &b){
	if(a.slope==b.slope)
		return (b.b-a.a)*(a.b-a.a)>0;
	return a.slope<b.slope;
}

point inter(seg a,seg b){
	double A1=a.a.y-a.b.y,B1=a.b.x-a.a.x,C1=a.a*a.b;
	double A2=b.a.y-b.b.y,B2=b.b.x-b.a.x,C2=b.a*b.b;
	double d=A1*B2-B1*A2;
	point cur;
	cur.x=(B1*C2-B2*C1)/d;
	cur.y=(A2*C1-A1*C2)/d;
	return cur;
}

bool cal(seg a,seg b,seg c){
	point cur=inter(b,c);
	return (cur-a.a)*(a.b-a.a)>0;
}

bool judge(int k){
	int cnt=0;
	for(int i=1;i<=2*n;i++)
		if(l[i].id<=k && l[i].slope!=s[cnt].slope)
			s[++cnt]=l[i];
	int head=1,tail=2;
	Q[1]=s[1],Q[2]=s[2];
	for(int i=3;i<=cnt;i++){
		while(head<tail && cal(s[i],Q[tail],Q[tail-1])) tail--;
		while(head<tail && cal(s[i],Q[head],Q[head+1])) head++;
		Q[++tail]=s[i];
	}
	while(head<tail && cal(Q[head],Q[tail],Q[tail-1])) tail--;
	while(head<tail && cal(Q[tail],Q[head],Q[head+1])) head++;
	if(tail-head>=2) return true;
	return false;
}

int main(){
    freopen("bzoj2732.in","r",stdin);
    cin>>n;
    for(int i=1;i<=n;i++){
    	scanf("%lf%lf%lf",&x,&y,&z);
    	l[i*2-1].make(1,z/x-x,0,z/x);
    	l[i*2].make(0,y/x,1,y/x-x);
    	l[i*2-1].id=l[i*2].id=i;
    }
    sort(l+1,l+2*n+1,cmp);
    int L=1,R=n;
    while(L<=R){
    	int mid=(L+R)>>1;
    	if(judge(mid)) ans=mid,L=mid+1;
    	else R=mid-1;
    }
    printf("%d",ans);
    return 0;
}