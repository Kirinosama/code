#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

#define eps 1e-8
#define MAXN 510
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

struct node{
	int x,y;
	void in(){scanf("%d%d",&x,&y);}
	node operator -(const node &a){
		return (node){y-a.y,x-a.x};
	}
	double operator *(const node &a){
		return x*a.y-y*a.x;
	}
}p[MAXN];

struct line{
	node a,b;
	double ang;
	void make(node p,node q){
		a=p,b=q;
		ang=atan2(b.y-a.y,b.x-a.x);
	}
}l[MAXN];

int comp(double a,double b){
	if(fabs(a-b)<eps) return 0;
	else if(a<b) return -1;
	else return 1;
}

int isleft(line a,node b){
	double res=(a.a-b)*(a.b-b);
	if(abs(res)<eps) return 0;
	else if(res>0) return 1;
	else return -1;
}

bool cmp(const line &a,const line &b){
	if(!comp(a.ang,b.ang))
		return isleft(b,a.a)>=0;
	return a.ang<b.ang;
}

int n,m,cnt;

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
 	for(int i=1;i<=cnt;i++)
 		printf("(%d,%d) (%d,%d)\n",l[i].a.x,l[i].a.y,l[i].b.x,l[i].b.y);
    return 0;
}
