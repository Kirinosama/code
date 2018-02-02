#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

#define eps 1e-10
#define MAXN 500010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int n,cnt,head,tail;
bool flag;

struct point{
	double x,y;
	point(){}
	point(double x_,double y_){x=x_,y=y_;}
	point operator - (const point &a)const{
		return point(x-a.x,y-a.y);
	}
	point operator + (const point &a)const{
		return point(x+a.x,y+a.y);
	}
	double dis(const point &a)const{
		return (x-a.x)*(x-a.x)+(y-a.y)*(y-a.y);
	}
	double cross(const point &a)const{
		return x*a.y-y*a.x;
	}
}p[MAXN],Q[MAXN];

struct query{
	int c,res;
	double x,y;
}q[MAXN];

bool onright(point a,point b,point c){
	return (b-c).cross(a-c)>=0;
}

bool cmp(const point &a,const point &b){
	if(a.x==b.x)return a.y<b.y;
	return a.x<b.x;
}

bool cmp1(const point &a,const point &b){
	double res=(a-p[1]).cross(b-p[1]);
	if(res>eps) return true;
	else if(fabs(res)<=eps) return p[1].dis(a)<p[1].dis(b);
	else return false;
}

bool out(point a,point b){
	return b.dis(a)>a.dis(point(0,0))+eps;
}

void judge(query &cur){
	double k;
	if(cur.y==0.0) k=INF;
	else k=-cur.x/cur.y;
	if(cnt<=2){
		for(int i=1;i<=cnt;i++)
			if(out(p[i],point(cur.x,cur.y))){
				cur.res=0;break;
			}
	}else if(k>0){
		for(int i=head;i<tail;i++)
	}else{

	}
}

void solve(){
	head=1,tail=2;int tp=1;
	for(int i=2;i<=cnt;i++)
		if(cmp(p[i],p[tp])) tp=i;
	swap(p[1],p[tp]);
	sort(p+2,p+cnt+1,cmp1);
	Q[1]=p[1],Q[2]=p[2];
	for(int i=3;i<=n;i++){
		if(head<tail && onright(Q[tail-1],Q[tail],p[i]))tail--;
		Q[++tail]=p[i];
	}
}

void cdq(int l,int r){
	if(l==r)return;
	int mid=(l+r)>>1;cnt=0;
	for(int i=l;i<=mid;i++)if(!q[i].c){
		p[++cnt]=point(q[i].x,q[i].y);
	}
	if(cnt>2) solve();
	for(int i=mid+1;i<=r;i++)if(q[i].c && q[i].res){
		judge(q[i]);
	}
	cdq(l,mid);cdq(mid+1,r);
}

int main(){
    freopen("bzoj2961.in","r",stdin);
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
    	scanf("%d%lf%lf",&q[i].c,&q[i].x,&q[i].y);
    	if(!q[i].c)flag=true;
    	if(flag)q[i].res=1;
    	else q[i].res=0;
    }
    cdq(1,n);
    for(int i=1;i<=n;i++)if(q[i].c){
    	if(q[i].res)printf("Yes\n");
    	else printf("No\n");
    }
    return 0;
}