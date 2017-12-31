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
#define MAXM 510
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

struct point{
	int x,y,lastnum;
	double lastlen;
	void in(){
		scanf("%d %d",&x,&y);
		lastlen=0.0;lastnum=0;
	}
}d[MAXN];

struct edge{
	point a,b;
	double l;
	void in(){
		a.in(),b.in();
		scanf("%lf",&l);
	}
}s[MAXM],S;

double f(int x){
	return (double)x*double(x);
}

double dis(point x,point y){
	return sqrt(f(y.x-x.x)+f(y.y-x.y));
}

int isonright(point a,point b,point c){
	int res=(c.x-a.x)*(b.y-a.y)-(c.y-a.y)*(b.x-a.x);
	if(res==0) return 0;
	if(res>0) return 1;
	return -1;
}

bool cmp(const point &a,const point &b){
	if((dis(a,S.a)<=S.l+eps)>(dis(b,S.a)<=S.l+eps))
		return true;
	if(isonright(S.a,S.b,a)>isonright(S.a,S.b,b))
		return true;
	int c=isonright(S.a,a,b);
	if(c==1) return true;
	if(c==-1) return false;
	return dis(S.a,a)>dis(S.a,b);
}

int n,m,t;

void make(){
	int res=1;
	for(int i=1;i<=n;i++)
		d[i].lastnum=0;
	while(1){
		sort(d+1,d+1+n,cmp);
		if(dis(d[1],S.a)>S.l) break;
		res++;S.l-=dis(d[1],S.a);
		if(d[1].lastnum && d[1].lastlen-S.l<S.l){
			double roundlen=d[1].lastlen-S.l;
			int cnt=(int)(S.l/roundlen);
			int round=res-d[1].lastnum;
			res+=round*cnt;
			S.l-=roundlen*(double)cnt;
			d[1].lastnum=res,d[1].lastlen=S.l;
		}
		else{
			d[1].lastnum=res,d[1].lastlen=S.l;
		}
		int tx=d[1].x,ty=d[1].y;
		S.b.x=tx+S.b.x-S.a.x;
		S.b.y=ty+S.b.y-S.a.y;
		S.a.x=tx,S.a.y=ty;
	}
	printf("%d\n",res);
}

void solve(){
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++)
		d[i].in();
	for(int i=1;i<=m;i++){
		s[i].in();S=s[i];
		make();
	}
}

int main(){
    freopen("game.in","r",stdin);
    freopen("game.out","w",stdout);
    cin>>t;
    while(t--)
    	solve();
    return 0;
}