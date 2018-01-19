#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <queue>
using namespace std;

#define eps 1e-8
#define MAXN 510
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

struct node{
	double x,y;
	void in(){scanf("%d%d",&x,&y);}
	node operator -(const node &a){
		return (node){x-a.x,y-a.y};
	}
	double operator *(const node &a){
		return x*a.y-y*a.x;
	}
}p[MAXN],ans[MAXN];

struct line{
	node a,b;
	double ang;
	void make(node p,node q){
		a=p,b=q;
		ang=atan2(b.y-a.y,b.x-a.x);
	}
}l[MAXN],Q[MAXN*2];

int n,m,cnt,anscnt;

int comp(double a,double b){
	if(fabs(a-b)<eps) return 0;
	else if(a<b) return -1;
	else return 1;
}

int isleft(line a,node b){
	double res=(a.a-b)*(a.b-b);
	if(fabs(res)<eps) return 0;
	else if(res>0) return 1;
	else return -1;
}

bool cmp(const line &a,const line &b){
	if(!comp(a.ang,b.ang))
		return isleft(b,a.a)>=0;
	return a.ang<b.ang;
}

node getintersect(line a,line b){
	node cur;
	double A1=a.a.y-a.b.y,B1=a.b.x-a.a.x,C1=a.a*a.b;
	double A2=b.a.y-b.b.y,B2=b.b.x-b.a.x,C2=b.a*b.b;
	double d=A1*B2-A2*B1;
	cur.x=(double)(B1*C2-B2*C1)/d;
	cur.y=(double)(A2*C1-A1*C2)/d;
	return cur;
}

bool judge(line a,line b,line c){
	node cur=getintersect(b,c);
	return isleft(a,cur)<=0;
}

void solve(){
	int head=1,tail=2;
	Q[1]=l[1],Q[2]=l[2];
	for(int i=3;i<=cnt;i++){
		while(head<tail && judge(l[i],Q[tail],Q[tail-1])) tail--;
		while(head<tail && judge(l[i],Q[head],Q[head+1])) head++;
		Q[++tail]=l[i];
	}
	while(head<tail && judge(Q[head],Q[tail],Q[tail-1])) tail--;
	while(head<tail && judge(Q[tail],Q[head],Q[head+1])) head++;
	Q[++tail]=Q[head];
	for(int i=head;i<tail;i++){
		ans[++anscnt]=getintersect(Q[i],Q[i+1]);
		printf("(%d,%d)\n",ans[anscnt].x,ans[anscnt].y);
	}
}

int main(){
    freopen("bzoj2618.in","r",stdin);
    cin>>n;
    while(n--){
    	cin>>m;
    	for(int i=1;i<=m;i++)
    		p[i].in();
    	for(int i=1;i<=m;i++)
    		l[++cnt].make(p[i],p[i==m?1:i+1]);
    }
    sort(l+1,l+1+cnt,cmp);int cnt1=0;
    for(int i=1;i<=cnt;i++)
    	if(comp(l[i].ang,l[cnt1].ang)) l[++cnt1]=l[i];
 	cnt=cnt1;
 	solve();
    return 0;
}
